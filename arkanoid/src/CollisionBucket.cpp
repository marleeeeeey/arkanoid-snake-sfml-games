#include "CollisionBucket.h"

CollisionBucket::CollisionBucket(
    std::vector<std::shared_ptr<IObject>>& primaryObjects, std::vector<std::shared_ptr<IObject>>& secondaryObjects,
    OnBumpingCallback cb )
  : m_primaryObjects( primaryObjects ), m_secondaryObjects( secondaryObjects ), m_onBumpingCallback( std::move( cb ) )
{
    for ( const auto& primaryObject : m_primaryObjects )
        primaryObject->setOnBumpingCallBack( m_onBumpingCallback );
}

void CollisionBucket::process() const
{
    for ( const auto& primaryObject : m_primaryObjects )
        primaryObject->checkBumping( m_secondaryObjects );
}
