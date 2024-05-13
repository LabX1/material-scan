void GetComponentsInChildren(uintptr_t GameObject, std::vector<uintptr_t>& renderers) {
	if (GameObject == 0) return; // Rebuilt by Cjweb.
 
	auto componentList = threads::Read<uint64_t>(GameObject + 0x30);
	int componentSize = threads::Read<int>(GameObject + 0x40);
 
	for (int j = 0; j < componentSize; ++j) {
		uintptr_t component = threads::Read<uint64_t>(componentList + (0x10 * j + 0x8));
		if (component == 0) continue;
 
		auto componentInst = threads::Read<uint64_t>(component + 0x28);
		if (componentInst == 0) continue;
		auto componentObject = threads::Read<uint64_t>(componentInst + 0x0);
		if (componentObject == 0) continue;
		auto componentName = threads::Read<uint64_t>(componentObject + 0x10);
		if (componentName == 0) continue;
		std::string Name = threads::ReadASCII(componentName);
 
		log_to_file("[Component]: " + Name);// + " [" + std::to_string(componentSize) + "]");
 
		if (Name == "SkinnedMeshRenderer") {
			renderers.push_back(component);
		}
		if (Name == "Transform") {
			uintptr_t childList = threads::Read<uint64_t>(component + 0x70);
			int childSize = threads::Read<int>(component + 0x80);
 
			for (int i = 0; i < childSize; ++i) {
				uint64_t childTransform = threads::Read<uint64_t>(childList + (0x8 * i));
				if (childTransform == 0) continue;
 
				auto childGameObject = threads::Read<uint64_t>(childTransform + 0x30);
				if (childGameObject == 0) continue;
				auto childGameObjectName = threads::Read<uint64_t>(childGameObject + 0x60);
				if (childGameObject == 0) continue;
				std::string childName = threads::ReadASCII(childGameObjectName);
 
				log_to_file("[Child]: " + childName + " [" + std::to_string(childSize) + "]");
 
				GetComponentsInChildren(childGameObject, renderers);
			}
		}
	}
}