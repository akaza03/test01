#ifdef _DEBUG

#include <Windows.h>
#include "_DebugConOut.h"

std::unique_ptr<_DebugConOut,_DebugConOut::_DebugConOutDeleter> _DebugConOut::s_Instance(new _DebugConOut);


_DebugConOut::_DebugConOut()
{
	////	�O�ɂ���E�B���h�E�̃n���h�����擾����
	HWND hWnd = GetForegroundWindow();

	//	�f�o�b�O�E�B���h�E��\������
	AllocConsole();

	//	������̏o��
	freopen_s(&_debugFp,"CONOUT$","w",stdout);
	//	������̓���
	freopen_s(&_debugFp,"CONIN$", "r", stdin);


	////	�Q�[���̃E�B���h�E���f�o�b�O�E�B���h�E���O�ɕ\������
	SetForegroundWindow(hWnd);
}


_DebugConOut::~_DebugConOut()
{
	FreeConsole();
}


#endif // _DEBUG