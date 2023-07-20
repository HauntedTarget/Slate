#include "ModelManager.h"


namespace bls
{
	ModelManager g_modelLib;

	std::shared_ptr<Model> bls::ModelManager::Get(const std::string& filename)
	{
		//Check if file doesn't exist
		if (m_models.find(filename) == m_models.end()) 
		{
			std::shared_ptr<Model> model = std::make_shared<Model>();

			model->Load(filename);

			m_models[filename] = model;
		}

		return m_models[filename];
	}
}
