

namespace AK_Base {

	Sprite2DManager::Sprite2DManager(BaseWindow* const game)
		: Actor(game)
	{
	}
	Sprite2DManager::~Sprite2DManager()
	{

	}


	// �\��ς݂̃��X�g���̕���`��
	void Sprite2DManager::Render()
	{


		const auto immediateContext = m_Game->AK_Base::BaseWindow::GetImmediateContext();
		const auto swapChain = m_Game->AK_Base::BaseWindow::GetSwapChain();
		const auto constantBuffer = m_Game->AK_Base::BaseWindow::GetConstantBuffer();
		const auto renderTargetView = m_Game->AK_Base::BaseWindow::GetRenderTargetView();
		const auto trans2D = m_Game->AK_Base::BaseWindow::GetTrans2DMatrix();


		// �w�i�h��Ԃ��i�|���j
		immediateContext->ClearRenderTargetView(renderTargetView, DirectX::Colors::MidnightBlue);


		// �R���X�^���g�o�b�t�@���쐬
		ConstantBuffer cb = {};
		cb.Trans2D = *trans2D;

		immediateContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

		// �q�N���X��`��
		Actor::Render();


		// ��ŏ��������o�b�N�o�b�t�@�ƌÂ���ʂ����ւ�
		swapChain->Present(1, 0);
	}
}