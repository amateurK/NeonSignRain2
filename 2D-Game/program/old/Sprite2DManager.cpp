

namespace AK_Base {

	Sprite2DManager::Sprite2DManager(BaseWindow* const game)
		: Actor(game)
	{
	}
	Sprite2DManager::~Sprite2DManager()
	{

	}


	// 予約済みのリスト内の物を描画
	void Sprite2DManager::Render()
	{


		const auto immediateContext = m_Game->AK_Base::BaseWindow::GetImmediateContext();
		const auto swapChain = m_Game->AK_Base::BaseWindow::GetSwapChain();
		const auto constantBuffer = m_Game->AK_Base::BaseWindow::GetConstantBuffer();
		const auto renderTargetView = m_Game->AK_Base::BaseWindow::GetRenderTargetView();
		const auto trans2D = m_Game->AK_Base::BaseWindow::GetTrans2DMatrix();


		// 背景塗りつぶし（掃除）
		immediateContext->ClearRenderTargetView(renderTargetView, DirectX::Colors::MidnightBlue);


		// コンスタントバッファを作成
		ConstantBuffer cb = {};
		cb.Trans2D = *trans2D;

		immediateContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

		// 子クラスを描画
		Actor::Render();


		// 上で準備したバックバッファと古い画面を入れ替え
		swapChain->Present(1, 0);
	}
}