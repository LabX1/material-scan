// Misc code that would be used with GetComponentsInChildren showing how to properly access viewModel and apply chams.

void ProcessSkinnedMeshRenderer(uintptr_t renderer) {
	if (renderer == 0) return;
	
	// Requires size be least 2 if its 1 it wont work.
	for (std::uint32_t idx{ 0 }; idx < 2; idx++) {
		const auto renderEntry = threads::Read<uintptr_t>(renderer + 0x20 + (idx * 0x8));
		if (!renderEntry)
			continue;

		const auto untity_object = threads::Read<uintptr_t>(renderEntry + 0x10);
		if (!untity_object)
			continue;

		const auto mat_list = threads::Read<dynamic_array>(untity_object + 0x148);
		if (mat_list.sz < 1 || mat_list.sz > 5)
			continue;

		for (std::uint32_t idx{ 0 }; idx < mat_list.sz; idx++) {
			threads::Write<unsigned int>(mat_list.base + (idx * 0x4), globals::handChamMaterial);
		}
	}
}

// Example of using GetComponentsInChildren

std::vector<uintptr_t> renderers;
std::vector<uintptr_t> materials;
std::lock_guard<std::mutex> lock(mtx);
GetComponentsInChildren(globals::viewModel, renderers);
for (auto renderer : renderers) {
	ProcessSkinnedMeshRenderer(renderer);
}

// Getting viewModel for hand/weapon chams.

auto get_view_model() -> uint64_t {
	auto held = threads::Read<uint64_t>(reinterpret_cast<uint64_t>(this) + offsets::item::held_entity); // 0xB0
	auto viewModel = threads::Read<uint64_t>(held + offsets::heldentity::viewModel);
	auto viewModelInstance = threads::Read<uint64_t>(viewModel + 0x30);
	auto baseViewModel = threads::Read<uint64_t>(viewModelInstance + 0x10);
	
	// Required if not false will cause chams to apply to world and break camera movement.
	threads::Write<bool>(viewModelInstance + 0x40, false); // useViewModelCamera
	return threads::Read<uint64_t>(baseViewModel + 0x30);
}

