struct dynamic_array
{
	std::uint64_t base;
	std::uint64_t mem_id;
	std::uint64_t sz;
	std::uint64_t cap;
};

// Loop through player list to apply chams to players.
for (auto entityLoop : entities)
{
	auto skinnedMultiMesh = threads::Read<uintptr_t>(playerModel + offsets::playermodel::multi_mesh); // _multiMesh
	auto SkinnedRenderersList = threads::Read<uintptr_t>(skinnedMultiMesh + 0x78); // List<Renderer> <Renderers>k__BackingField;
	auto SkinnedList = threads::Read<uintptr_t>(SkinnedRenderersList + 0x10);
	int materialsCount = threads::Read<int>(SkinnedRenderersList + 0x18);

	for (std::uint32_t idx{ 0 }; idx < materialsCount; idx++) {
		const auto renderEntry = threads::Read<uintptr_t>(SkinnedList + 0x20 + (idx * 0x8));
		if (!renderEntry)
			continue;

		const auto untity_object = threads::Read<uintptr_t>(renderEntry + 0x10);
		if (!untity_object)
			continue;

		const auto mat_list = threads::Read<dynamic_array>(untity_object + 0x148);
		if (mat_list.sz < 1 || mat_list.sz > 5)
			continue;

		for (std::uint32_t idx{ 0 }; idx < mat_list.sz; idx++) {
			threads::Write<unsigned int>(mat_list.base + (idx * 0x4), globals::chamMaterial);

		}
	}
}