// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SEditorViewportViewMenu.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EditorStyleSet.h"
#include "EditorViewportCommands.h"
#include "RayTracingDebugVisualizationMenuCommands.h"
#include "RenderResource.h"

#define LOCTEXT_NAMESPACE "EditorViewportViewMenu"

void SEditorViewportViewMenu::Construct( const FArguments& InArgs, TSharedRef<SEditorViewport> InViewport, TSharedRef<class SViewportToolBar> InParentToolBar )
{
	Viewport = InViewport;
	MenuExtenders = InArgs._MenuExtenders;

	SEditorViewportToolbarMenu::Construct
	(
		SEditorViewportToolbarMenu::FArguments()
			.ParentToolBar( InParentToolBar)
			.Cursor( EMouseCursor::Default )
			.Label(this, &SEditorViewportViewMenu::GetViewMenuLabel)
			.LabelIcon(this, &SEditorViewportViewMenu::GetViewMenuLabelIcon)
			.OnGetMenuContent( this, &SEditorViewportViewMenu::GenerateViewMenuContent )
	);
}

FText SEditorViewportViewMenu::GetViewMenuLabel() const
{
	FText Label = LOCTEXT("ViewMenuTitle_Default", "View");
	TSharedPtr< SEditorViewport > PinnedViewport = Viewport.Pin();
	if( PinnedViewport.IsValid() )
	{
		switch( PinnedViewport->GetViewportClient()->GetViewMode() )
		{
			case VMI_BrushWireframe:
				Label = LOCTEXT("ViewMenuTitle_BrushWireframe", "Wireframe");
				break;

			case VMI_Wireframe:
				Label = LOCTEXT("ViewMenuTitle_Wireframe", "Wireframe");
				break;

			case VMI_Unlit:
				Label = LOCTEXT("ViewMenuTitle_Unlit", "Unlit");
				break;

			case VMI_Lit:
				Label = LOCTEXT("ViewMenuTitle_Lit", "Lit");
				break;

#if RHI_RAYTRACING
			case VMI_PathTracing:
				Label = LOCTEXT("ViewMenuTitle_PathTracing", "Path Tracing");
				break;

			case VMI_RayTracingDebug:
				Label = LOCTEXT("ViewMenuTitle_RayTracingDebug", "Ray Tracing Debug");
				break;
#endif

			case VMI_Lit_DetailLighting:
				Label = LOCTEXT("ViewMenuTitle_DetailLighting", "Detail Lighting");
				break;

			case VMI_LightingOnly:
				Label = LOCTEXT("ViewMenuTitle_LightingOnly", "Lighting Only");
				break;

			case VMI_LightComplexity:
				Label = LOCTEXT("ViewMenuTitle_LightComplexity", "Light Complexity");
				break;

			case VMI_ShaderComplexity:
				Label = LOCTEXT("ViewMenuTitle_ShaderComplexity", "Shader Complexity");
				break;

			case VMI_QuadOverdraw:
				Label = LOCTEXT("ViewMenuTitle_QuadOverdraw", "Quad Overdraw");
				break;

			case VMI_ShaderComplexityWithQuadOverdraw:
				Label = LOCTEXT("ViewMenuTitle_ShaderComplexityWithQuadOverdraw", "Shader Complexity & Quads");
				break;

			case VMI_PrimitiveDistanceAccuracy:
				Label = LOCTEXT("ViewMenuTitle_PrimitiveDistanceAccuracy", "Primitive Distance Accuracy");
				break;

			case VMI_MeshUVDensityAccuracy:
				Label = LOCTEXT("ViewMenuTitle_MeshUVDensityAccuracy", "Mesh UV Densities Accuracy");
				break;

			case VMI_MaterialTextureScaleAccuracy:
				Label = LOCTEXT("ViewMenuTitle_MaterialTextureScaleAccuracy", "Material Texture Scales Accuracy");
				break;

			case VMI_RequiredTextureResolution:
				Label = LOCTEXT("ViewMenuTitle_Required Texture Resolution", "Required Texture Resolution");
				break;

			case VMI_StationaryLightOverlap:
				Label = LOCTEXT("ViewMenuTitle_StationaryLightOverlap", "Stationary Light Overlap");
				break;

			case VMI_LightmapDensity:
				Label = LOCTEXT("ViewMenuTitle_LightmapDensity", "Lightmap Density");
				break;

			case VMI_ReflectionOverride:
				Label = LOCTEXT("ViewMenuTitle_ReflectionOverride", "Reflections");
				break;

			case VMI_VisualizeBuffer:
				Label = LOCTEXT("ViewMenuTitle_VisualizeBuffer", "Buffer Visualization");
				break;

			case VMI_CollisionPawn:
				Label = LOCTEXT("ViewMenuTitle_CollisionPawn", "Player Collision");
				break;

			case VMI_CollisionVisibility:
				Label = LOCTEXT("ViewMenuTitle_CollisionVisibility", "Visibility Collision");
				break;

			case VMI_LitLightmapDensity:
				break;

			case VMI_LODColoration:
				Label = LOCTEXT("ViewMenuTitle_LODColoration", "LOD Coloration");
				break;

			case VMI_HLODColoration:
				Label = LOCTEXT("ViewMenuTitle_HLODColoration", "HLOD Coloration");
				break;
		}
	}

	return Label;
}

const FSlateBrush* SEditorViewportViewMenu::GetViewMenuLabelIcon() const
{
	FName Icon = NAME_None;
	TSharedPtr< SEditorViewport > PinnedViewport = Viewport.Pin();
	if( PinnedViewport.IsValid() )
	{
		static FName WireframeIcon( "EditorViewport.WireframeMode" );
		static FName UnlitIcon( "EditorViewport.UnlitMode" );
		static FName LitIcon( "EditorViewport.LitMode" );
		static FName DetailLightingIcon("EditorViewport.DetailLightingMode");
		static FName LightingOnlyIcon("EditorViewport.LightingOnlyMode");
		static FName LightComplexityIcon("EditorViewport.LightComplexityMode");
		static FName ShaderComplexityIcon("EditorViewport.ShaderComplexityMode");
		static FName QuadOverdrawIcon("EditorViewport.QuadOverdrawMode");
		static FName ShaderComplexityWithQuadOverdrawIcon("EditorViewport.ShaderCOmplexityWithQuadOverdrawMode");
		static FName PrimitiveDistanceAccuracyIcon("EditorViewport.TexStreamAccPrimitiveDistanceMode");
		static FName MeshUVDensityAccuracyIcon("EditorViewport.TexStreamAccMeshUVDensityMode");
		static FName MaterialTextureScaleAccuracyIcon("EditorViewport.TexStreamAccMaterialTextureScaleMode");
		static FName RequiredTextureResolutionIcon("EditorViewport.RequiredTextureResolutionMode");
		static FName LightOverlapIcon("EditorViewport.StationaryLightOverlapMode");
		static FName LightmapDensityIcon("EditorViewport.LightmapDensityMode");
		static FName ReflectionModeIcon("EditorViewport.ReflectionOverrideMode");
		static FName LODColorationIcon("EditorViewport.LODColorationMode");
		static FName VisualizeBufferIcon("EditorViewport.VisualizeBufferMode");
		static FName CollisionPawnIcon("EditorViewport.CollisionPawn");
		static FName CollisionVisibilityIcon("EditorViewport.CollisionVisibility");

		switch( PinnedViewport->GetViewportClient()->GetViewMode() )
		{
			case VMI_BrushWireframe:
				Icon = WireframeIcon;
				break;

			case VMI_Wireframe:
				Icon = WireframeIcon;
				break;

			case VMI_Unlit:
				Icon = UnlitIcon;
				break;

			case VMI_Lit:
				Icon = LitIcon;
				break;

#if RHI_RAYTRACING
			// #dxr_todo: UE-72550 use special icons for ray tracing view modes
			case VMI_RayTracingDebug:
				Icon = LitIcon; 
				break;

			case VMI_PathTracing:
				Icon = LitIcon; 
				break;
#endif
			case VMI_Lit_DetailLighting:
				Icon = DetailLightingIcon;
				break;

			case VMI_LightingOnly:
				Icon = LightingOnlyIcon;
				break;

			case VMI_LightComplexity:
				Icon = LightComplexityIcon;
				break;

			case VMI_ShaderComplexity:
				Icon = ShaderComplexityIcon;
				break;

			case VMI_QuadOverdraw:
				Icon = QuadOverdrawIcon;
				break;

			case VMI_ShaderComplexityWithQuadOverdraw:
				Icon = ShaderComplexityWithQuadOverdrawIcon;
				break;

			case VMI_PrimitiveDistanceAccuracy:
				Icon = PrimitiveDistanceAccuracyIcon;
				break;

			case VMI_MeshUVDensityAccuracy:
				Icon = MeshUVDensityAccuracyIcon;
				break;

			case VMI_MaterialTextureScaleAccuracy:
				Icon = MaterialTextureScaleAccuracyIcon;
				break;

			case VMI_RequiredTextureResolution:
				Icon = RequiredTextureResolutionIcon;
				break;

			case VMI_StationaryLightOverlap:
				Icon = LightOverlapIcon;
				break;

			case VMI_LightmapDensity:
				Icon = LightmapDensityIcon;
				break;

			case VMI_ReflectionOverride:
				Icon = ReflectionModeIcon;
				break;

			case VMI_VisualizeBuffer:
				Icon = VisualizeBufferIcon;
				break;

			case VMI_CollisionPawn:
				Icon = CollisionPawnIcon;
				break;

			case VMI_CollisionVisibility:
				Icon = CollisionVisibilityIcon;
				break;

			case VMI_LitLightmapDensity:
				break;

			case VMI_LODColoration:
				Icon = LODColorationIcon;
				break;

			case VMI_HLODColoration:
				Icon = LODColorationIcon;
				break;

			case VMI_GroupLODColoration:
				Icon = LODColorationIcon;
				break;
		}
	}

	return FEditorStyle::GetBrush(Icon);
}

TSharedRef<SWidget> SEditorViewportViewMenu::GenerateViewMenuContent() const
{
	const FEditorViewportCommands& BaseViewportActions = FEditorViewportCommands::Get();

	const bool bInShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder ViewMenuBuilder(bInShouldCloseWindowAfterMenuSelection, Viewport.Pin()->GetCommandList(), MenuExtenders);

	{
		// View modes
		{
			ViewMenuBuilder.BeginSection("ViewMode", LOCTEXT("ViewModeHeader", "View Mode") );
			{
				ViewMenuBuilder.AddMenuEntry(BaseViewportActions.LitMode, NAME_None, LOCTEXT("LitViewModeDisplayName", "Lit"));
				ViewMenuBuilder.AddMenuEntry(BaseViewportActions.UnlitMode, NAME_None, LOCTEXT("UnlitViewModeDisplayName", "Unlit"));
				ViewMenuBuilder.AddMenuEntry(BaseViewportActions.WireframeMode, NAME_None, LOCTEXT("BrushWireframeViewModeDisplayName", "Wireframe"));
				ViewMenuBuilder.AddMenuEntry(BaseViewportActions.DetailLightingMode, NAME_None, LOCTEXT("DetailLightingViewModeDisplayName", "Detail Lighting"));
				ViewMenuBuilder.AddMenuEntry(BaseViewportActions.LightingOnlyMode, NAME_None, LOCTEXT("LightingOnlyViewModeDisplayName", "Lighting Only"));
				ViewMenuBuilder.AddMenuEntry(BaseViewportActions.ReflectionOverrideMode, NAME_None, LOCTEXT("ReflectionOverrideViewModeDisplayName", "Reflections"));
				ViewMenuBuilder.AddMenuEntry(BaseViewportActions.CollisionPawn, NAME_None, LOCTEXT("CollisionPawnViewModeDisplayName", "Player Collision"));
				ViewMenuBuilder.AddMenuEntry(BaseViewportActions.CollisionVisibility, NAME_None, LOCTEXT("CollisionVisibilityViewModeDisplayName", "Visibility Collision"));
			}

#if RHI_RAYTRACING
			if (IsRayTracingEnabled())
			{
				const FEditorViewportCommands& BaseViewportCommands = FEditorViewportCommands::Get();
				ViewMenuBuilder.AddMenuEntry(BaseViewportCommands.PathTracingMode, NAME_None, LOCTEXT("PathTracingViewModeDisplayName", "Path Tracing"));
			}
#endif

			// Optimization
			{
				struct Local
				{
					static void BuildOptimizationMenu( FMenuBuilder& Menu, TWeakPtr< SViewportToolBar > InParentToolBar )
					{
						const FEditorViewportCommands& BaseViewportCommands = FEditorViewportCommands::Get();

						UWorld* World = GWorld;
						const ERHIFeatureLevel::Type FeatureLevel = (IsInGameThread() && World) ? (ERHIFeatureLevel::Type)World->FeatureLevel : GMaxRHIFeatureLevel;

						Menu.BeginSection("OptimizationViewmodes", LOCTEXT("OptimizationSubMenuHeader", "Optimization Viewmodes"));
						{
							if (FeatureLevel == ERHIFeatureLevel::SM5)
							{
								Menu.AddMenuEntry(BaseViewportCommands.LightComplexityMode, NAME_None, LOCTEXT("LightComplexityViewModeDisplayName", "Light Complexity"));
								Menu.AddMenuEntry(BaseViewportCommands.LightmapDensityMode, NAME_None, LOCTEXT("LightmapDensityViewModeDisplayName", "Lightmap Density"));
								Menu.AddMenuEntry(BaseViewportCommands.StationaryLightOverlapMode, NAME_None, LOCTEXT("StationaryLightOverlapViewModeDisplayName", "Stationary Light Overlap"));
							}

							Menu.AddMenuEntry(BaseViewportCommands.ShaderComplexityMode, NAME_None, LOCTEXT("ShaderComplexityViewModeDisplayName", "Shader Complexity"));

							if (AllowDebugViewShaderMode(DVSM_ShaderComplexityContainedQuadOverhead, GMaxRHIShaderPlatform, FeatureLevel))
							{
								Menu.AddMenuEntry(BaseViewportCommands.ShaderComplexityWithQuadOverdrawMode, NAME_None, LOCTEXT("ShaderComplexityWithQuadOverdrawViewModeDisplayName", "Shader Complexity & Quads"));
							}
							if (AllowDebugViewShaderMode(DVSM_QuadComplexity, GMaxRHIShaderPlatform, FeatureLevel))
							{
								Menu.AddMenuEntry(BaseViewportCommands.QuadOverdrawMode, NAME_None, LOCTEXT("QuadOverdrawViewModeDisplayName", "Quad Overdraw"));
							}
						}
						Menu.EndSection();

						Menu.BeginSection("TextureStreaming", LOCTEXT("TextureStreamingHeader", "Texture Streaming Accuracy") );
						if ( AllowDebugViewShaderMode(DVSM_PrimitiveDistanceAccuracy, GMaxRHIShaderPlatform, FeatureLevel) && (!InParentToolBar.IsValid() || InParentToolBar.Pin()->IsViewModeSupported(VMI_PrimitiveDistanceAccuracy)) )
						{
							Menu.AddMenuEntry( BaseViewportCommands.TexStreamAccPrimitiveDistanceMode, NAME_None, LOCTEXT("TexStreamAccPrimitiveDistanceViewModeDisplayName", "Primitive Distance") );
						}
						if ( AllowDebugViewShaderMode(DVSM_MeshUVDensityAccuracy, GMaxRHIShaderPlatform, FeatureLevel) && (!InParentToolBar.IsValid() || InParentToolBar.Pin()->IsViewModeSupported(VMI_MeshUVDensityAccuracy)) )
						{
							Menu.AddMenuEntry(BaseViewportCommands.TexStreamAccMeshUVDensityMode, NAME_None, LOCTEXT("TexStreamAccMeshUVDensityViewModeDisplayName", "Mesh UV Densities"));
						}
						// TexCoordScale accuracy viewmode requires shaders that are only built in the TextureStreamingBuild, which requires the new metrics to be enabled.
						if ( AllowDebugViewShaderMode(DVSM_MaterialTextureScaleAccuracy, GMaxRHIShaderPlatform, FeatureLevel) && CVarStreamingUseNewMetrics.GetValueOnAnyThread() != 0 && (!InParentToolBar.IsValid() || InParentToolBar.Pin()->IsViewModeSupported(VMI_MaterialTextureScaleAccuracy)) )
						{
							Menu.AddMenuEntry(BaseViewportCommands.TexStreamAccMaterialTextureScaleMode, NAME_None, LOCTEXT("TexStreamAccMaterialTextureScaleViewModeDisplayName", "Material Texture Scales"));
						}
						if ( AllowDebugViewShaderMode(DVSM_RequiredTextureResolution, GMaxRHIShaderPlatform, FeatureLevel) && (!InParentToolBar.IsValid() || InParentToolBar.Pin()->IsViewModeSupported(VMI_MaterialTextureScaleAccuracy)) )
						{
							Menu.AddMenuEntry(BaseViewportCommands.RequiredTextureResolutionMode, NAME_None, LOCTEXT("RequiredTextureResolutionModeDisplayName", "Required Texture Resolution"));
						}
						Menu.EndSection();
					}
				};

				ViewMenuBuilder.AddSubMenu( LOCTEXT("OptimizationSubMenu", "Optimization Viewmodes"), LOCTEXT("Optimization_ToolTip", "Select optimization visualizer"), FNewMenuDelegate::CreateStatic( &Local::BuildOptimizationMenu, ParentToolBar ) );
			}

#if RHI_RAYTRACING
			if (IsRayTracingEnabled())
			{
				struct Local
				{
					static void BuildRayTracingDebugMenu(FMenuBuilder& Menu, TWeakPtr< SViewportToolBar > InParentToolBar)
					{
						const FRayTracingDebugVisualizationMenuCommands& RtDebugCommands = FRayTracingDebugVisualizationMenuCommands::Get();
						RtDebugCommands.BuildVisualisationSubMenu(Menu);
					}
				};

				ViewMenuBuilder.AddSubMenu(LOCTEXT("RayTracingDebugSubMenu", "Ray Tracing Debug"), LOCTEXT("RayTracing_ToolTip", "Select ray tracing buffer visualization view modes"), FNewMenuDelegate::CreateStatic(&Local::BuildRayTracingDebugMenu, ParentToolBar));
			}
#endif

			{
				struct Local
				{
					static void BuildLODMenu(FMenuBuilder& Menu)
					{
						Menu.BeginSection("LevelViewportLODColoration", LOCTEXT("LODModesHeader", "Level of Detail Coloration"));
						{
							Menu.AddMenuEntry(FEditorViewportCommands::Get().LODColorationMode, NAME_None, LOCTEXT("LODColorationModeDisplayName", "Mesh LODs"));
							Menu.AddMenuEntry(FEditorViewportCommands::Get().HLODColorationMode, NAME_None, LOCTEXT("HLODColorationModeDisplayName", "Hierarchical LODs"));
						}
						Menu.EndSection();
					}
				};

				ViewMenuBuilder.AddSubMenu(LOCTEXT("VisualizeGroupedLODDisplayName", "Level of Detail Coloration"), LOCTEXT("GroupedLODMenu_ToolTip", "Select a mode for LOD Coloration"), FNewMenuDelegate::CreateStatic(&Local::BuildLODMenu), /*Default*/false, FSlateIcon(FEditorStyle::GetStyleSetName(), "EditorViewport.GroupLODColorationMode"));
			}

			ViewMenuBuilder.EndSection();
		}

		// Auto Exposure
		{
			const FEditorViewportCommands& BaseViewportCommands = FEditorViewportCommands::Get();

			TSharedRef<SWidget> FixedEV100Menu = Viewport.Pin()->BuildFixedEV100Menu();
			TSharedPtr<FEditorViewportClient> EditorViewPostClient = Viewport.Pin()->GetViewportClient();
			const bool bIsLevelEditor = EditorViewPostClient.IsValid() && EditorViewPostClient->IsLevelEditorClient();

			ViewMenuBuilder.BeginSection("Exposure", LOCTEXT("ExposureHeader", "Exposure"));
			ViewMenuBuilder.AddMenuEntry( bIsLevelEditor ? BaseViewportCommands.ToggleInGameExposure : BaseViewportCommands.ToggleAutoExposure, NAME_None );
			ViewMenuBuilder.AddWidget( FixedEV100Menu, LOCTEXT("FixedEV100", "EV100") );
			ViewMenuBuilder.EndSection();
		}
	}
	return ViewMenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
