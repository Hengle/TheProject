#ifndef AABB_H
#define AABB_H


class AABB
{
public:
    AABB();
    AABB(const glm::vec3 & min_point, const glm::vec3 & max_point);
    virtual ~AABB();

    void Reset(const glm::vec3 & point);
    void AddPoint(const glm::vec3 & point);
    void Translate(const glm::vec3 & offset);

    bool IsPointInside(const glm::vec3 & point) const;
    bool CollidesWith(const AABB & other) const;
    bool CollidesWith(const glm::vec3 & aabb_min, const glm::vec3 & aabb_max) const;
    bool CollidesWithRay(const glm::vec3 & rayStart, const glm::vec3 & rayInverseDirection) const;

    glm::vec3 GetExtent() const;
    const glm::vec3 & GetMin() const;
    const glm::vec3 & GetMax() const;

protected:
    glm::vec3 m_min, m_max;
};

#endif // SG_AABB_H
