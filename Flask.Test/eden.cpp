#include "tpch.h"
#include <eden/eden.h>

using namespace Nova;

enum class Type : meta::smallest::uint<meta::bit(5)> {
	None = meta::bit(0),
	A = meta::bit(1),
	B = meta::bit(2),
	C = meta::bit(3),
	D = meta::bit(4),
	E = meta::bit(5),
	All = A | B | C | D | E
};

constexpr Type shift(Type type, size_t shift = 1) {
	return static_cast<Type>(static_cast<std::underlying_type_t<Type>>(type) << shift);
}

struct Event : public eden::Event<Type> {
	using Eden::Eden;
};

using Dispatcher = Nova::eden::Dispatcher<Event, 5>;

class Eden : public ::testing::Test {
protected:
	Dispatcher dispatcher;
	// void SetUp() override {}
	// void TearDown() override {}
};
#define NOVA_TEST_EDEN(name) TEST_F(Eden, name)

NOVA_TEST_EDEN(Subscribe_InBounds) {
	for (auto i = Type::A; i <= Type::E; i = shift(i)) {
		EXPECT_NO_THROW(dispatcher.subscribe(i, [](auto&& event) { return false; }));
	}
}

NOVA_TEST_EDEN(Subscribe_OutOfBounds) {
	for (auto i = 1; i <= 3; ++i)
		EXPECT_THROW(dispatcher.subscribe(shift(Type::E, i), [](auto&& event) { return false; }), std::domain_error);
}

#define _IMPL_EXPECT_COUNT(count, value) EXPECT_EQ(count, value) << "Mismatching Calls to fire and the number of subscribed functions!"
#define EXPECT_COUNT(value) _IMPL_EXPECT_COUNT(count, value)
#define EXPECT_COUNTS(index, value) _IMPL_EXPECT_COUNT(counts ## index, value)

NOVA_TEST_EDEN(Fire) {
	for (auto type = Type::A; type <= Type::E; type = shift(type)) {
		auto count = 0;

		EXPECT_COUNT(0);
		EXPECT_NO_THROW(dispatcher.fire(type));
		EXPECT_COUNT(0);
		dispatcher.subscribe(type, [&](auto&& event) {
			++count;
			return false;
		}).orphan();
		EXPECT_NO_THROW(dispatcher.fire(type));
		EXPECT_COUNT(1);
		EXPECT_NO_THROW(dispatcher.fire(type));
		EXPECT_NO_THROW(dispatcher.fire(type));
		EXPECT_COUNT(3);
		dispatcher.subscribe(type, [&](auto&& event) {
			++count;
			EXPECT_EQ(event.desc, type) << "Event description does not match the type the event has been subscribed to!";
			return false;
		}).orphan();
		EXPECT_NO_THROW(dispatcher.fire(type));
		EXPECT_COUNT(5);
		dispatcher.subscribe(type, [&](auto&& event) {
			++count;
			EXPECT_FALSE(true) << "Should not be called as it has not been orphaned and will be removed!";
			return false;
		});
		EXPECT_NO_THROW(dispatcher.fire(type));
		EXPECT_COUNT(7);
		{
			auto ticket = dispatcher.subscribe(type, [&](auto&& event) {
				++count;
				return true;
			});
			EXPECT_NO_THROW(dispatcher.fire(type));
			EXPECT_COUNT(10);
			auto ticket_2 = dispatcher.subscribe(type, [&](auto&& event) {
				++count;
				EXPECT_FALSE(true) << "Should not be called as the previous event handler returned true";
				return false;
			});
			EXPECT_NO_THROW(dispatcher.fire(type));
			EXPECT_COUNT(13);
		}
		dispatcher.subscribe(type, [&](auto&& event) {
			++count;
			throw std::runtime_error{ "This event handler should throw! " };
			return false;
		}).orphan();
		EXPECT_THROW(dispatcher.fire(type), std::runtime_error) << "Expected the error from the event handler to be propegated back to the fire command!";
		EXPECT_COUNT(16);
	}
}

// Single Function, Single Event Type
NOVA_TEST_EDEN(Subscribe_Single_Single) {
	for (auto type = Type::A; type <= Type::E; type = shift(type)) {
		auto count = 0;
		auto lambda = [&](auto&& event) { ++count; return false; };

		ASSERT_NO_THROW(dispatcher.subscribe(type, lambda).orphan());
		EXPECT_COUNT(0);
		dispatcher.fire(type);
		EXPECT_COUNT(1);
		dispatcher.fire(type);
		EXPECT_COUNT(2);
		ASSERT_NO_THROW(dispatcher.subscribe(type, lambda).orphan());
		ASSERT_NO_THROW(dispatcher.subscribe(type, lambda).orphan());
		dispatcher.fire(type);
		EXPECT_COUNT(5);
	}
}

// Multiple Function, Single Event Types
NOVA_TEST_EDEN(Subscribe_Group_Single) {
	for (auto type = Type::A; type <= Type::E; type = shift(type)) {
		auto count = 0;
		auto lambda = [&](auto&& event) { ++count; return false; };

		ASSERT_NO_THROW(dispatcher.subscribe({
			{ type, lambda },
			{ type, lambda },
			{ type, lambda },
			}).orphan());
		EXPECT_COUNT(0);
		dispatcher.fire(type);
		EXPECT_COUNT(3);
		dispatcher.fire(type);
		EXPECT_COUNT(6);
		dispatcher.fire(Type::None);
		EXPECT_COUNT(6);
		ASSERT_NO_THROW(dispatcher.subscribe({
			{ type, lambda },
			{ type, lambda },
			}).orphan());
		EXPECT_COUNT(6);
		dispatcher.fire(type);
		EXPECT_COUNT(11);
	}
}

// Single Function, Multiple Event Types
NOVA_TEST_EDEN(Subscribe_Single_Group) {
	auto count = 0;
	auto lambda = [&](auto&& event) { ++count; return false; };

	for (auto type_a = Type::A; type_a <= Type::D; type_a = shift(type_a)) {
		dispatcher.clear();
		auto type_b = shift(type_a);
		auto type = type_a | type_b;
		auto counts = std::array{ 0, 0 };
		auto count = 0;
		auto lambda = [&](Event& event) {
			{
				auto i = 0;
				for (auto&& t : { type_a , type_b }) {
					if (event.is(t))
						++counts[i];
					++i;
				}
			}
			++count;
			return false;
		};

		ASSERT_NO_THROW(dispatcher.subscribe(type, lambda).orphan());
		EXPECT_COUNT(0);
		EXPECT_COUNTS([0], 0);
		EXPECT_COUNTS([1], 0);

		dispatcher.fire(type_a);
		EXPECT_COUNT(1);
		EXPECT_COUNTS([0], 1);
		EXPECT_COUNTS([1], 0);

		dispatcher.fire(type_b);
		EXPECT_COUNT(2);
		EXPECT_COUNTS([0], 1);
		EXPECT_COUNTS([1], 1);

		dispatcher.fire(type);
		EXPECT_COUNT(4);
		EXPECT_COUNTS([0], 3);
		EXPECT_COUNTS([1], 3);

		dispatcher.fire(type);
		EXPECT_COUNT(6);
		EXPECT_COUNTS([0], 5);
		EXPECT_COUNTS([1], 5);

		ASSERT_NO_THROW(dispatcher.subscribe(type, lambda).orphan());
		ASSERT_NO_THROW(dispatcher.subscribe(type, lambda).orphan());

		dispatcher.fire(type_a);
		EXPECT_COUNT(9);
		EXPECT_COUNTS([0], 8);
		EXPECT_COUNTS([1], 5);

		dispatcher.fire(type_b);
		EXPECT_COUNT(12);
		EXPECT_COUNTS([0], 8);
		EXPECT_COUNTS([1], 8);

		dispatcher.fire(type);
		EXPECT_COUNT(18);
		EXPECT_COUNTS([0], 14);
		EXPECT_COUNTS([1], 14);
	}

}

// Multiple Functions, Multiple Event Types
NOVA_TEST_EDEN(Subscribe_Group_Group) {
	for (auto type_a = Type::A; type_a <= Type::D; type_a = shift(type_a)) {
		dispatcher.clear();
		auto type_b = shift(type_a);
		auto type = type_a | type_b;
		auto counts = std::array{ 0, 0 };
		auto count = 0;
		auto lambda = [&](Event& event) {
			{
				auto i = 0;
				for (auto&& t : { type_a , type_b }) {
					if (event.is(t))
						++counts[i];
					++i;
				}
			}
			++count;
			return false;
		};

		ASSERT_NO_THROW(dispatcher.subscribe({
			{type, lambda},
			{type, lambda},
			{type, lambda},
			}).orphan());
		EXPECT_COUNT(0);
		EXPECT_COUNTS([0], 0);
		EXPECT_COUNTS([1], 0);

		dispatcher.fire(type_a);
		EXPECT_COUNT(3);
		EXPECT_COUNTS([0], 3);
		EXPECT_COUNTS([1], 0);

		dispatcher.fire(type_b);
		EXPECT_COUNT(6);
		EXPECT_COUNTS([0], 3);
		EXPECT_COUNTS([1], 3);

		dispatcher.fire(type);
		EXPECT_COUNT(12);
		EXPECT_COUNTS([0], 9);
		EXPECT_COUNTS([1], 9);

		dispatcher.fire(type);
		EXPECT_COUNT(18);
		EXPECT_COUNTS([0], 15);
		EXPECT_COUNTS([1], 15);

		ASSERT_NO_THROW(dispatcher.subscribe({
			{type, lambda},
			{type, lambda},
			{type, lambda},
			}).orphan());
		ASSERT_NO_THROW(dispatcher.subscribe({
			{type, lambda},
			{type, lambda},
			{type, lambda},
			}).orphan());

		dispatcher.fire(type_a);
		EXPECT_COUNT(27);
		EXPECT_COUNTS([0], 24);
		EXPECT_COUNTS([1], 15);

		dispatcher.fire(type_b);
		EXPECT_COUNT(36);
		EXPECT_COUNTS([0], 24);
		EXPECT_COUNTS([1], 24);

		dispatcher.fire(type);
		EXPECT_COUNT(54);
		EXPECT_COUNTS([0], 42);
		EXPECT_COUNTS([1], 42);

	}
}
