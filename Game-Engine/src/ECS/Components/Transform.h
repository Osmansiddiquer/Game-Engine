#pragma once
#include <cmath>
#include "ECS/Component.h"
#include <Core/Math/Math.h> 

namespace Engine 
{
    using namespace Math;
    class Transform : public Component {
    public:
        Vector3 position;
        Quaternion rotation;
        Vector3 scale;

        Transform(const Vector3& pos = Vector3(0.0f), const Quaternion& rot = Quaternion::identity(), const Vector3& scl = Vector3(1.0f))
            : position(pos), rotation(rot), scale(scl) {}

        void translate(const Vector3& offset) {
            position += offset;
        }

        void translate(float offsetX, float offsetY, float offsetZ) {
            translate(Vector3(offsetX, offsetY, offsetZ));
        }

        void rotate(const Vector3& eulerAngles) {
            Quaternion rotationOffset = Quaternion::FromEulerAngles(eulerAngles);
            rotation = rotationOffset * rotation;
        }

        void rotate(float angle, const Vector3& axis) {
            Quaternion rotationOffset = Quaternion::FromAngleAxis(axis, angle);
            rotation = rotationOffset * rotation;
        }

        void scaleBy(const Vector3& scaleFactor) {
            scale.x *= scaleFactor.x;
            scale.y *= scaleFactor.y;
            scale.z *= scaleFactor.z;
        }

        void scaleBy(float scaleValue) {
            scale *= scaleValue;
        }

        void lookAt(const Vector3& target, const Vector3& up = {0.0f, 1.0f, 0.0f}) {
            Vector3 direction = (target - position).Normalized();
            rotation = Quaternion::FromLookRotation(direction, up);
        }

        Matrix4 getModelMatrix() const {
            Matrix4 modelMatrix = Matrix4::identity;
            modelMatrix *= glm::translate(modelMatrix, position);
            modelMatrix = modelMatrix * rotation.toMatrix();
            modelMatrix = glm::scale(modelMatrix, scale);
            return modelMatrix;
        }
    };
}
