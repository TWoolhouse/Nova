#include "tpch.h"
#include <nvtl/weave.h>

using namespace Nova::nvtl;

using WeaveT = Nova::nvtl::Weave<int, 9>;
class nvtl_Weave : public ::testing::Test {
protected:
	WeaveT weave;
	// void SetUp() override {}
	// void TearDown() override {}
};
#define NOVA_TEST_WEAVE(name) TEST_F(nvtl_Weave, name)

NOVA_TEST_WEAVE(DirectThreadAccess) {
	auto count = 0;
	for (auto&& thread : weave) ++count;
	EXPECT_EQ(count, weave.size()) << "Mismatch in the number of threads accessible and available";

	for (auto i = 0; i < weave.size(); ++i) {
		EXPECT_NO_THROW(weave[i]) << "Unable to access thread of index: " << i;
		EXPECT_NO_THROW(weave.at(i)) << "Unable to access thread of index: " << i;
	}
	for (auto i = 0; i < 3; ++i) {
		const auto idx = weave.size() + i;
		EXPECT_THROW(weave.at(idx), std::out_of_range) << "Able to access threads beyond size(" << weave.size() << "): " << idx;
	}
}

NOVA_TEST_WEAVE(ThreadsIterator_Forward) {
	auto count = 0;
	for (auto&& thread : weave) {
		EXPECT_EQ(&thread, &weave[count++]) << "Input Iterator: Thread is not returned in the expected order";
	}

	count = 0;
	for (auto&& thread : weave) {
		EXPECT_EQ(&thread, &weave[count++]) << "Forward Iterator: Thread is incorrect after reiterating";
	}
}

NOVA_TEST_WEAVE(ThreadsIterator_Types) {
	auto count = 0;

	count = 0;
	const auto& cweave = weave;
	for (auto&& thread : cweave) {
		EXPECT_EQ(&thread, &weave[count++]) << "ConstFwdIter: Thread is not returned in the expected order";
	}
	count = weave.size();
	for (auto&& thread : std::views::reverse(weave)) {
		EXPECT_EQ(&thread, &weave[--count]) << "RevIter: Thread is not returned in the expected order";
	}
	count = weave.size();
	for (auto&& thread : std::views::reverse(cweave)) {
		EXPECT_EQ(&thread, &weave[--count]) << "ConstRevIter: Thread is not returned in the expected order";
	}
}

NOVA_TEST_WEAVE(ThreadIterator_Forward) {
	for (auto i = 0; i < weave.size(); ++i)
		for (auto j = 0; j < i; ++j)
			weave.push_back(i, j);

	{
		auto i = 0;
		for (auto&& thread : weave) {
			auto j = 0;
			for (auto&& elm : thread) {
				ASSERT_EQ(elm, j) << "Woven elements are not returned in the expected order! on thread: " << i;
				++j;
			}
			++i;
		}
	}

	{
		auto i = 0;
		for (auto&& thread : weave) {
			auto j = 0;
			for (auto&& elm : thread) {
				ASSERT_EQ(elm, j) << "Woven elements are incorrect after reiterating! on thread: " << i;
				++j;
			}
			++i;
		}
	}

}

NOVA_TEST_WEAVE(IsInitiallyEmpty) {
	for (auto&& thread : weave)
		for (auto&& obj : thread)
			EXPECT_TRUE(false) << "Something was found in the weave: " << obj;
}

template<typename Input>
void test_weave_thread_fwd_iter(const WeaveT& weave, const Input& input, const size_t& index) {
	auto i = 0;
	for (auto&& element : weave[index]) {
		ASSERT_EQ(input[i++], element) << "Element has not been inserted correctly";
	}
}

NOVA_TEST_WEAVE(Insertion_SingleBlocks) {
	constexpr std::array input{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (auto index = 0; index < weave.size(); ++index) {
		for (auto&& i : input) {
			weave.push_back(index, i);
		}
		test_weave_thread_fwd_iter(weave, input, index);
	}
}

NOVA_TEST_WEAVE(Insertion_MultiBlocks_SplitArgs) {
	weave.push_back(
		0, 1,
		1, 2,
		2, 3,
		3, 4,
		4, 5,
		5, 6,
		6, 7,
		7, 8,
		8, 9
	);
	for (auto i = 0; i < weave.size(); ++i) {
		test_weave_thread_fwd_iter(weave, std::array{ i + 1 }, i);
	}
}

NOVA_TEST_WEAVE(Insertion_MultiBlocks_PairArgs) {
	weave.push_back({
		{ 0, 1 },
		{ 1, 2 },
		{ 2, 3 },
		{ 3, 4 },
		{ 4, 5 },
		{ 5, 6 },
		{ 6, 7 },
		{ 7, 8 },
		{ 8, 9 }
	});
	for (auto i = 0; i < weave.size(); ++i) {
		test_weave_thread_fwd_iter(weave, std::array{ i + 1 }, i);
	}
}
