#include "GameObject.h"


void GameObject::Draw(bls::Renderer& renderer)
{
	m_model.Draw(renderer, m_transform);
}
