// ShaderGalleryScene.cpp

#include "ShaderGalleryScene.h"
#include "ShaderPane.h"

ShaderGalleryScene::ShaderGalleryScene()
{
}

ShaderGalleryScene::~ShaderGalleryScene()
{
}

void ShaderGalleryScene::InitPanesGL()
{
    for (std::vector<Pane*>::iterator it = m_panes.begin();
        it != m_panes.end();
        ++it)
    {
        Pane* pP = *it;
        if (pP == NULL)
            continue;
        pP->initGL();
    }
}

Pane* ShaderGalleryScene::AddShaderPane(ShaderToy* pSt)
{
    ShaderPane* pP = new ShaderPane();
    if (pP == NULL)
        return NULL;

    const int idx = static_cast<int>(m_panes.size());
    ///@todo Scalable positioning
    const glm::vec3 pos(-8.0f + static_cast<float>(idx)*1.1f, 1.5f, -2.0f);
    pP->m_tx.SetPosition(pos);
    pP->m_tx.SetDefaultPosition(pos);

    const glm::mat4 ori = glm::mat4(1.0f);
    pP->m_tx.SetDefaultOrientation(ori);
    pP->m_tx.SetOrientation(ori);

    pP->m_pShadertoy = pSt;

    m_panes.push_back(pP);

    return pP;
}

ShaderToy* ShaderGalleryScene::GetFocusedShader() const
{
    int idx = 0;
    for (std::vector<Pane*>::const_iterator it = m_panes.begin();
        it != m_panes.end();
        ++it, ++idx)
    {
        const ShaderPane* pP = reinterpret_cast<ShaderPane*>(*it);
        if (pP == NULL)
            continue;
        if (pP->m_cursorInPane)
            return pP->m_pShadertoy;
    }

    return NULL;
}
