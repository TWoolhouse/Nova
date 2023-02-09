#include "fpch.h"
#include <iostream>

using namespace Nova;

using Model = mlb::vec3;
using Input = mlb::vec2;
using Classification = float;

const std::array<std::pair<Input, Classification>, 6> DATASET = {
	std::pair{ Input{1, 4}, 1 },
	std::pair{ Input{2, 9}, 1 },
	std::pair{ Input{5, 6}, 1 },
	std::pair{ Input{4, 5}, 1 },
	std::pair{ Input{6, 0.7}, -1 },
	std::pair{ Input{1, 1.5}, -1 }
};
using Dataset = std::remove_cvref_t<decltype(DATASET)>;

constexpr auto activation_step(float value) {
	if (value > 0) return 1;
	else if (value < 0) return -1;
	else return 0;
}

constexpr bool row(Model& model, const Input& input, const Classification classification) {
	Model input_with_bias = {1.0f, input};
	auto result = activation_step(mlb::dot(model, input_with_bias));
	if (result == classification) return true;
	model += classification * input_with_bias;
	return false;
}

constexpr bool epoch(Model& model, const Dataset& dataset) {
	size_t success = 0;
	for (const auto& [input, classification] : dataset)
		success += row(model, input, classification);
	return success >= dataset.size();
}

constexpr size_t train(Model& model, const Dataset& dataset) {
	size_t count = 0;
	while (!epoch(model, dataset)) ++count;
	return count;
}



int NOVA_MAIN(int argc, const char** argv) {
	bark::Initialize();
	Model model{0};
	blip::Timer timer;
	auto epochs = train(model, DATASET);
	timer.update();
	nova_bark_info("Epochs: {} in {}", epochs, std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(timer.elapsed()));
	bark::Terminate();
	return 0;
}
