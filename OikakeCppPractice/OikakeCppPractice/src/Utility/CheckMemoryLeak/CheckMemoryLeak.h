#pragma once

/**
 * @file CheckMemoryLeak.h
 * @brief ���������[�N���Ă��邩�`�F�b�N����N���X�̒�`�t�@�C��
 * @author ���]
 * @date Unknown
 */

#include<crtdbg.h>

 /*! @class CheckMemoryLeak
 *   @brief  ���������[�N���Ă��邩�`�F�b�N����N���X�̒�`
 */
class CheckMemoryLeak {
public:
	 /// <summary>
	 /// �R���X�g���N�^<see cref="CheckMemoryLeak"/>
	 /// </summary>
	CheckMemoryLeak() {
		//!���������[�N���o�̓E�B���h�E�ɕ\������֐�
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_MODE_FILE);
	}
	/**
	* @brief number��ڂ̃������m�ێ��Ƀu���C�N����悤�ݒ�
	* @param number number��ڂ̃������m�ێ�
	* @detail
	* ���������[�N�����Ƃ��A�o�̓E�B���h�E��
	* 
	* 	Detected memory leaks!
	* 	Dumping objects ->
	*   {52992} normal block at 0x000000001E27F290, 72 bytes long.
	* 	Data:                  01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	* 	Object dump complete.
	* 
	* 	�݂����ȕ��͂��o�Ă���B
	* 
	* 	52992��ڂɊm�ۂ���72�o�C�g�̃����������[�N�����Ƃ����Ӗ��B
	* 	����52992��ڂŃ��[�N����ꍇ�́A�����Ńu���C�N���邱�ƂŁA
	* 	�������킩�邩������Ȃ��B
	* 
	* 	_CrtSetBreakAlloc(52992);
	* 
	* ���̊֐���52992��ڂ̃������m�ێ��Ƀu���C�N����Ƃ����֐�
	*/	
	void SetBreakPoint(int number) {
		_CrtSetBreakAlloc(number);
	}
};

