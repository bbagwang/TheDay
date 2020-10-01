// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDEventManager.h"

UTDEventManager::UTDEventManager()
{

}

void UTDEventManager::UpdateBulletSpread(FVector2D BulletSpread)
{
	BulletSpreadUpdate.Broadcast(BulletSpread);
}
