void GenerateTexturedMoons (SOLARSYS_STATE *system, PLANET_DESC *planet)
{
	COUNT i;
	FRAME SurfFrame;
	PLANET_DESC *pMoonDesc;
	PLANET_DESC *previousOrbitalDesc;
	previousOrbitalDesc = pSolarSysState->pOrbitalDesc;
	
	for (i = 0, pMoonDesc = &system->MoonDesc[0];
			i < planet->NumPlanets; ++i, ++pMoonDesc)
	{
		SurfFrame = NULL;
	
		// BW : precompute the generated texture to display it in IP
		if (!(pMoonDesc->data_index & WORLD_TYPE_SPECIAL))
		{
			DoPlanetaryAnalysis (&pSolarSysState->SysInfo, pMoonDesc);
			
			if (CurStarDescPtr->Index == SOL_DEFINED)
				pSolarSysState->SysInfo.PlanetInfo.AxialTilt = 0;

			pSolarSysState->pOrbitalDesc = pMoonDesc;

			if (CurStarDescPtr->Index == SOL_DEFINED)
			{	// png defined moons in Sol
			
				COUNT curr_planet_index = planetIndex (pSolarSysState, planet);
		
				if (curr_planet_index == 2)
				{
					// EARTH
					switch (i)
					{
						case 1: /* LUNA */
							SurfFrame = CaptureDrawable (LoadGraphic (IP_LUNA_MASK_ANIM));
							break;
					}
				}
				else if (curr_planet_index == 4)
				{
					// JUPITER
					switch (i)
					{
						case 0: /* IO */
							SurfFrame = CaptureDrawable (LoadGraphic (IP_IO_MASK_ANIM));
							break;
						case 1: /* EUROPA */
							SurfFrame = CaptureDrawable (LoadGraphic (IP_EUROPA_MASK_ANIM));
							break;
						case 2: /* GANYMEDE */
							SurfFrame = CaptureDrawable (LoadGraphic (IP_GANYMEDE_MASK_ANIM));
							break;
						case 3: /* CALLISTO */
							SurfFrame = CaptureDrawable (LoadGraphic (IP_CALLISTO_MASK_ANIM));
							break;
					}
				}
				else if (curr_planet_index == 5)
				{
					// SATURN
					switch (i)
					{
						case 0: /* TITAN */
							SurfFrame = CaptureDrawable (LoadGraphic (IP_TITAN_MASK_ANIM));
							break;
					}
				}
				else if (curr_planet_index == 7)
				{
					// NEPTUNE
					switch (i)
					{
						case 0: /* TRITON */
							SurfFrame = CaptureDrawable (LoadGraphic (IP_TRITON_MASK_ANIM));
							break;
					}
				}
			}

			GeneratePlanetSurfaceForIP (pMoonDesc, SurfFrame, GENERATE_MOON_PERIMETER, GENERATE_MOON_DIAMETER);
			pMoonDesc->orbit = pSolarSysState->Orbit;
			PrepareNextRotationFrameForIP (pMoonDesc, 0);

			// Clean up some parasitic use of pSolarSysState
			LockMutex (GraphicsLock);
			// DestroyDrawable (ReleaseDrawable (pSolarSysState->Orbit.TintFrame));
			// pSolarSysState->Orbit.TintFrame = 0;
			// pSolarSysState->Orbit.TintColor = BLACK_COLOR;
		
			// DestroyDrawable (ReleaseDrawable (pSolarSysState->Orbit.TopoZoomFrame));
			// pSolarSysState->Orbit.TopoZoomFrame = 0;
			DestroyStringTable (ReleaseStringTable (pSolarSysState->XlatRef));
			pSolarSysState->XlatRef = 0;
			DestroyDrawable (ReleaseDrawable (pSolarSysState->TopoFrame));
			pSolarSysState->TopoFrame = 0;
			DestroyColorMap (ReleaseColorMap (pSolarSysState->OrbitalCMap));
			pSolarSysState->OrbitalCMap = 0;
			UnlockMutex (GraphicsLock);
			// End clean up
		}
	}
	pSolarSysState->pOrbitalDesc = previousOrbitalDesc;
}