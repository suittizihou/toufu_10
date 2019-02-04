#pragma once

#include"Math/Vector3/Vector3.h"
#include"Actor/Base/ActorBase.h"
#include<vector>

/**
 * @file HitInfo.h
 * @brief �����蔻��̏����܂Ƃ߂��\���̒�`�t�@�C��
 * @author ���]
 * @date Unknown
 */


/*! @class HitInfo
 * @brief  �����蔻��̏����܂Ƃ߂��\����
 */
class HitInfo {
public:
	/*! @struct CollideContent
	* @brief  1vs1�̓����蔻����܂Ƃ߂��\����
	*/
	struct CollideContent {
		//!�ڐG���������̓����蔻��̔ԍ�
		int bodyID;
		//!�ڐG���������ActorBase�|�C���^
		ActorBase* collideActor;
		//!�ڐG�_
		Vector3 intersect;
	};
public:	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	HitInfo()
		: contents(0)
		, collideActor(nullptr)
	{
	}
public:
	//!�ڐG�����A�N�^�[��ۑ����Ă����z��
	std::vector<CollideContent> contents;
	ActorBase* collideActor;

};
