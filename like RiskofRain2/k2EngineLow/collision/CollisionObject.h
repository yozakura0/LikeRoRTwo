#pragma once
#include "physics/PhysicsGhostObject.h"

namespace nsK2EngineLow {
	
	class CollisionObject : public IGameObject
	{
	public:
		CollisionObject();
		~CollisionObject();
		bool Start();
		void Update();

		void CreateBox(Vector3 pos, Quaternion rot, Vector3 size)
		{
			m_physicsGhostObject.CreateBox(pos, rot, size);
		}

		void CreateSphere(Vector3 pos, Quaternion rot, float radius)
		{
			m_physicsGhostObject.CreateSphere(pos, rot, radius);
		}

		void CreateMesh(Vector3 pos, Quaternion rot, const Model& model, const Matrix& worldMatrix)
		{
			m_physicsGhostObject.CreateMesh(pos, rot, model, worldMatrix);
		}

		void SetTimeLimit(const float timeLimit)
		{
			m_timeLimit = timeLimit;
		}

		void SetName(const char* name)
		{
			m_name = name;
		}

		const char* GetName() const
		{
			return m_name;
		}

		void SetPosition(const Vector3& position)
		{
			m_physicsGhostObject.SetPosition(position);
		}

		void SetRotation(const Quaternion& rotation)
		{
			m_physicsGhostObject.SetRotation(rotation);
		}

		void SetWorldMatrix(const Matrix& matrix)
		{
			Vector3 position;
			position.x = matrix.m[3][0];
			position.y = matrix.m[3][1];
			position.z = matrix.m[3][2];
			SetPosition(position);
			Quaternion rotation;
			rotation.SetRotation(matrix);
			SetRotation(rotation);
		}

		void SetIsEnableAutoDelete(bool isFlag)
		{
			m_isEnableAutoDelete = isFlag;
		}

		const bool IsHit(CollisionObject* collisionObject) const
		{
			bool isCollision = false;
			PhysicsWorld::GetInstance()->ContactTest(&collisionObject->GetbtCollisionObject(), [&](const btCollisionObject& contactObject) {
				if (m_physicsGhostObject.IsSelf(contactObject) == true) {
					isCollision = true;
				}
				});
			return isCollision;
		}

		const bool IsHit(CharacterController& characterController) const
		{
			bool isCollision = false;
			PhysicsWorld::GetInstance()->ContactTest(characterController, [&](const btCollisionObject& contactObject) {
				if (m_physicsGhostObject.IsSelf(contactObject) == true) {
					isCollision = true;
				}
				});
			return isCollision;
		}

		PhysicsGhostObject& GetGhostObject()
		{
			return m_physicsGhostObject;
		}

		btCollisionObject& GetbtCollisionObject()
		{
			return m_physicsGhostObject.GetbtCollisionObject();
		}

		void SetIsEnable(bool isEnable)
		{
			m_isEnable = isEnable;
		}

		const bool IsEnable() const
		{
			return m_isEnable;
		}
	private:
		PhysicsGhostObject m_physicsGhostObject;
		const char*	m_name = nullptr;
		float m_timer = 0.0f;
		float m_timeLimit = 0.0f;
		bool m_isEnableAutoDelete = true;
		bool m_isEnable = true;
	};

	class CollisionObjectManager
	{
	public:
		CollisionObjectManager();
		~CollisionObjectManager();

		void AddCollisionObject(CollisionObject* collisionObject)
		{
			m_collisionObjectVector.push_back(collisionObject);
		}

		CollisionObject* FindCollisionObject(const char* name)
		{
			for (auto collisionObject : m_collisionObjectVector)
			{
				//名前一致！
				if (strcmp(collisionObject->GetName(), name) == 0)
				{
					//当たり判定が有効なら。
					if (collisionObject->IsEnable() == true)
					{
						return collisionObject;
					}
				}
			}
			return nullptr;
		}

		const CollisionObject* FindMatchForwardNameCollisionObject(const char* name) const
		{
			for (auto collisionObject : m_collisionObjectVector)
			{
				auto len = strlen(name);
				auto namelen = strlen(collisionObject->GetName());
				if (len > namelen) {
					//名前が長い。不一致。
					continue;
				}
				if (strncmp(name, collisionObject->GetName(), len) == 0)
				{
					//当たり判定が有効なら。
					if (collisionObject->IsEnable() == true)
					{
						return collisionObject;
					}
				}
			}
			return nullptr;
		}

		const std::vector<CollisionObject*>& FindCollisionObjects(const char* name)
		{
			m_findMatchForwardNameCollisionObjectVector.clear();
			for (auto collisionObject : m_collisionObjectVector)
			{
				//名前一致！
				if (strcmp(collisionObject->GetName(), name) == 0)
				{
					//当たり判定が有効なら。
					if (collisionObject->IsEnable() == true)
					{
						m_findMatchForwardNameCollisionObjectVector.push_back(collisionObject);
					}
				}
			}
			return m_findMatchForwardNameCollisionObjectVector;
		}

		const std::vector<CollisionObject*>& FindMatchForwardNameCollisionObjects(const char* name)
		{
			m_findsCollisionObjectVector.clear();
			for (auto collisionObject : m_collisionObjectVector)
			{
				auto len = strlen(name);
				auto namelen = strlen(collisionObject->GetName());
				if (len > namelen) {
					//名前が長い。不一致。
					continue;
				}
				if (strncmp(name, collisionObject->GetName(), len) == 0)
				{
					//当たり判定が有効なら。
					if (collisionObject->IsEnable() == true)
					{
						m_findsCollisionObjectVector.push_back(collisionObject);
					}
				}
			}
			return m_findsCollisionObjectVector;
		}

		void RemoveCollisionObject(CollisionObject* deleteCollisionObject)
		{
			for (auto it = m_collisionObjectVector.begin(); it != m_collisionObjectVector.end();) {
				// 条件一致した要素を削除する
				if (*it == deleteCollisionObject) {
					// 削除された要素の次を指すイテレータが返される。
					it = m_collisionObjectVector.erase(it);
				}
				// 要素削除をしない場合に、イテレータを進める
				else {
					++it;
				}
			}
		}
	private:
		std::vector<CollisionObject*> m_collisionObjectVector;
		std::vector<CollisionObject*> m_findsCollisionObjectVector;
		std::vector<CollisionObject*> m_findMatchForwardNameCollisionObjectVector;
	};
}