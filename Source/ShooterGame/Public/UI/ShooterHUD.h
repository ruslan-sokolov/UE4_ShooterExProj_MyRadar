// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ShooterTypes.h"
#include "ShooterRadarCollector.h"

#include "ShooterHUD.generated.h"


struct FHitData
{
	/** Last hit time. */
	float HitTime;
	
	/** strength of hit icon */
	float HitPercentage;

	/** Initialise defaults. */
	FHitData()
	{
		HitTime = 0.0f;
		HitPercentage = 0.0f;
	}
};

struct FDeathMessage
{
	/** Name of player scoring kill. */
	FString KillerDesc;

	/** Name of killed player. */
	FString VictimDesc;

	/** Killer is local player. */
	uint8 bKillerIsOwner : 1;
	
	/** Victim is local player. */
	uint8 bVictimIsOwner : 1;

	/** Team number of the killer. */
	int32 KillerTeamNum;

	/** Team number of the victim. */
	int32 VictimTeamNum; 

	/** timestamp for removing message */
	float HideTime;

	/** What killed the player. */
	TWeakObjectPtr<class UShooterDamageType> DamageType;

	/** Initialise defaults. */
	FDeathMessage()
		: bKillerIsOwner(false)
		, bVictimIsOwner(false)
		, KillerTeamNum(0)
		, VictimTeamNum(0)		
		, HideTime(0.f)
	{
	}
};

UCLASS()
class AShooterHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

protected:

	virtual void BeginPlay() override;

public:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Main HUD update loop. */
	virtual void DrawHUD() override;

	/**
	 * Sent from pawn hit, used to calculate hit notification overlay for drawing.
	 *
	 * @param	DamageTaken		The amount of damage.
	 * @param	DamageEvent		The actual damage event.
	 * @param	PawnInstigator	The pawn that did the damage.
	 */
	void NotifyWeaponHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator);

	/** Sent from ShooterWeapon, shows NO AMMO text. */
	void NotifyOutOfAmmo();

	/** Notifies we have hit the enemy. */
	void NotifyEnemyHit();

	/** 
	 * Set state of current mfatch.
	 *
	 * @param	NewState	The new match state.
	 */
	void SetMatchState(EShooterMatchState::Type NewState);

	/** Get state of current match. */
	EShooterMatchState::Type GetMatchState() const;

	/** Turns off scoreboard if it is being displayed */
	void ConditionalCloseScoreboard(bool bFocus = false);

	/** Toggles scoreboard */
	void ToggleScoreboard();

	/** 
	 * Toggles in game scoreboard.
	 * Note:Will not display if the game menu is visible.

	 * @param	bEnable	Required scoreboard display state.
	 * @param	bFocus	Give keyboard focus to the scoreboard.
	 * @return	true, if the scoreboard visibility changed
	 */
	bool ShowScoreboard(bool bEnable, bool bFocus = false);

	/** 
	 * Add death message.
	 *
	 * @param	KillerPlayerState	Player that did the killings state.
	 * @param	VictimPlayerState	Played that was killed state.
	 * @param	KillerDamageType	The type of damaged that caused the death.
	 */
	void ShowDeathMessage(class AShooterPlayerState* KillerPlayerState, class AShooterPlayerState* VictimPlayerState, const UDamageType* KillerDamageType);

	/*
	 * Toggle chat window visibility.
	 *
	 */
	void ToggleChat();

	/** 
	 * Set chat window visibility.
	 *
	 * @param	RequiredVisibility	The required visibility.
	 */
	void SetChatVisibilty( const EVisibility RequiredVisibility );

	/*
	 * Add a string to the chat window.
	 *
	 * @param	ChatString	The string to add.
	 * @param	bWantFocus	Should we set the chat window to focus
	 */
	void AddChatLine(const FText& ChatString, bool bWantFocus);

	/* Is the match over (IE Is the state Won or Lost). */
	bool IsMatchOver() const;
		
protected:
	/** Floor for automatic hud scaling. */
	static const float MinHudScale;

	/** Lighter HUD color. */
	FColor HUDLight;

	/** Darker HUD color. */
	FColor HUDDark;

	/** When we got last notice about out of ammo. */
	float NoAmmoNotifyTime;

	/** How long notice is fading out. */
	float NoAmmoFadeOutTime;

	/** Most recent hit time, used to check if we need to draw hit indicator at all. */
	float LastHitTime;

	/** How long till hit notify fades out completely. */
	float HitNotifyDisplayTime;

	/** When we last time hit the enemy. */
	float LastEnemyHitTime;

	/** How long till enemy hit notify fades out completely. */
	float LastEnemyHitDisplayTime;

	/** Icons for hit indicator. */
	UPROPERTY()
	FCanvasIcon HitNotifyIcon[8];

	/** kills background icon. */
	UPROPERTY()
	FCanvasIcon KillsBg;

	/** Match timer and player position background icon. */
	UPROPERTY()
	FCanvasIcon TimePlaceBg;

	/** Primary weapon background icon. */
	UPROPERTY()
	FCanvasIcon PrimaryWeapBg;

	/** Secondary weapon background icon */
	UPROPERTY()
	FCanvasIcon SecondaryWeapBg;

	/** Crosshair icons (left, top, right, bottom and center). */
	UPROPERTY()
	FCanvasIcon Crosshair[5];

	/** On crosshair indicator that we hit someone. */
	UPROPERTY()
	FCanvasIcon HitNotifyCrosshair;

	/** Death messages background icon. */
	UPROPERTY()
	FCanvasIcon DeathMessagesBg;

	/** Health bar background icon. */
	UPROPERTY()
	FCanvasIcon HealthBarBg;

	/** Health bar icon. */
	UPROPERTY()
	FCanvasIcon HealthBar;

	/** Health icon on the health bar. */
	UPROPERTY()
	FCanvasIcon HealthIcon;

	/** Kills icon. */
	UPROPERTY()
	FCanvasIcon KillsIcon;

	/** Bigger killed icon. */
	UPROPERTY()
	FCanvasIcon KilledIcon;

	/** Timer icon. */
	UPROPERTY()
	FCanvasIcon TimerIcon;

	/** Podium icon. */
	UPROPERTY()
	FCanvasIcon PlaceIcon;

	/** Radar North icon. */
	UPROPERTY()
	FCanvasIcon RadarNorthIcon;

	/** Radar circle icon. */
	UPROPERTY()
	FCanvasIcon RadarCircleIcon;

	/** Radar hit icon. */
	UPROPERTY()
	FCanvasIcon RadarHitIcon;

	/** Radar enemy icon. */
	UPROPERTY()
	FCanvasIcon RadarEnemyIcon;

	/** Radar pickup icon. */
	UPROPERTY()
	FCanvasIcon RadarPickupIcon;

	/** Radar up icon fragment. */
	UPROPERTY()
	FCanvasIcon RadarUpFragment;

	/** Radar down icon fragment. */
	UPROPERTY()
	FCanvasIcon RadarDownFragment;

	/** How many units in game radar can capture and show on hud **/
	UPROPERTY(EditDefaultsOnly)
		float RadarWorldAreaRadius;

	/** If Z axis differance is bigger then trashold then add "UP" and "Down" Icons on radar elements **/
	UPROPERTY(EditDefaultsOnly)
		float RadarIconHeightIndicatorTreshold;

	/** Radar booster icon. */

	/** UI scaling factor for other resolutions than Full HD. */
	float ScaleUI;

	/** Current animation pulse value. */
	float PulseValue;

	/** FontRenderInfo enabling casting shadow.s */
	FFontRenderInfo ShadowedFont;

	/** Big "KILLED [PLAYER]" message text above the crosshair. */
	FText CenteredKillMessage;

	/** last time we killed someone. */
	float LastKillTime;

	/** How long the message will fade out. */
	float KillFadeOutTime;

	/** Offsets to display hit indicator parts. */
	FVector2D Offsets[8];

	/** Texture for hit indicator. */
	UPROPERTY()
	UTexture2D* HitNotifyTexture;

	/** texture for HUD elements. */
	UPROPERTY()
	UTexture2D* HUDMainTexture;

	/** Texture for HUD elements. */
	UPROPERTY()
	UTexture2D* HUDAssets02Texture;

	/** Overlay shown when health is low. */
	UPROPERTY()
	UTexture2D* LowHealthOverlayTexture;

	/** Radar texture */
	UPROPERTY()
	UTexture2D* HUDRadarTexture;

	/** Large font - used for ammo display etc. */
	UPROPERTY()
	UFont* BigFont;

	/** Normal font - used for death messages and such. */
	UPROPERTY()
	UFont* NormalFont;

	/** General offset for HUD elements. */
	float Offset;

	/** Runtime data for hit indicator. */
	FHitData HitNotifyData[8];

	/** Active death messages. */
	TArray<FDeathMessage> DeathMessages;

	/** State of match. */
	EShooterMatchState::Type MatchState;

	/** Is the scoreboard widget on screen? */
	uint32 bIsScoreBoardVisible:1;

	/** Scoreboard widget. */
	TSharedPtr<class SShooterScoreboardWidget>	ScoreboardWidget;

	/** Scoreboard widget overlay. */
	TSharedPtr<class SOverlay>	ScoreboardWidgetOverlay;

	/** Scoreboard widget container - used for removing */
	TSharedPtr<class SWidget> ScoreboardWidgetContainer;

	/** Chatbox widget. */
	TSharedPtr<class SChatWidget> ChatWidget;

	/** Array of information strings to render (Waiting to respawn etc) */
	TArray<FCanvasTextItem> InfoItems;

	/** Called every time game is started. */
	virtual void PostInitializeComponents() override;

	/** 
	 * Converts floating point seconds to MM:SS string.
	 *
	 * @param TimeSeconds		The time to get a string for.
	 */
	FString GetTimeString(float TimeSeconds);

	/** Draws weapon HUD. */
	void DrawWeaponHUD();

	/** Draws kills information. */
	void DrawKills();

	/** Draw player's health bar. */
	void DrawHealth();

	/** Draws match timer and player position. */
	void DrawMatchTimerAndPosition();

	/** Draws weapon crosshair. */
	void DrawCrosshair();
	
	/** Draws hit indicator. */
	void DrawHitIndicator();

	/** Draw death messages. */
	void DrawDeathMessages();

	/*
	 * Acts same as Canvas->DrawIcon() with rotation options
	 * Use Canvas DrawItem under hood but with Chosen rotation/pivot for Item
	 */
	void DrawCanvasIconWithRot(FCanvasIcon& Icon, float X, float Y, float Scale, FRotator Rotation, FVector2D Pivot);

	/** 
	 * Draw player hit direction indicator on radar circle recieved from RadarCollector 
	 
	 * @param	TrackHitCharacterPos	Tracking hit character world location.
	 * @param	RadarCenter				RadarCenter on HUD Screen Space (should be scaled).
	 * @param	RadarRadius				RadarCircleIcon Radius (should be scaled).
	 * @param	RadarRotRadians			Radar Rotation from X World Axis
	 *
	 */
	void DrawRadarHitIndicator(FVector TrackHitCharacterPos, FVector2D RadarCenter, float RadarRadius, float RadarRotRadians);

	/**
	 * Draw RadarPoints Icons recieved from RadarCollector.

	 * @param	RadarPoints				Recieved RadarPoints Map from RadarCollector.
	 * @param	RadarWorldCenter		Actual Radar Center In World (Usually this is HUD Owned Player).
	 * @param	RadarCenter				RadarCenter on HUD Screen Space (should be scaled).
	 * @param	RadarRadius				RadarCircleIcon Radius (should be scaled).
	 * @param	RadarRotRadians			Radar Rotation from X World Axis
	 * @param	Icon					RadarPoint Icon to draw.
	 * @param	IconOffset				Icon point draw positive offset.
	 * @param	bShowHeightIndicator	Draws "Higher", "Lower" icons on top of Icon when Points Z axis is higher then RadarIconHeightIndicatorTreshold
	 * @param	HeightIndicatorOffset	"Higher", "Lower" icons positive offset
	 * @param	bHeightIndOffsetUseNegY	If true then HeightIndicatorOffset.Y for "Lower" will be -(HightIndicatorOffset.Y)
	 *                                  and for "Higher" will ramain HeightIndicatorOffset.Y
	 */
	void DrawRadarCollectorPoints(TMap<TWeakObjectPtr<AActor>, FRadarPoint> &RadarPoints, 
		FVector RadarWorldCenter, FVector2D RadarCenter, float RadarRadius, float RadarRotRadians,
		FCanvasIcon &Icon, FVector2D IconOffset = FVector2D::ZeroVector,
		bool bShowHeightIndicator = false, FVector2D HeightIndicatorOffset = FVector2D::ZeroVector, bool bHeightIndOffsetUseNegY = false);

	/** Draw Radar Circle, Radar North Icon, RadarPoints Icons, Radar Hit Direction Indicator */
	void DrawRadar();

	/** Class to recieve radar info from */
	class UShooterRadarCollector* RadarCollector;

	/** Delegate for telling other methods when players have started/stopped talking */
	FOnPlayerTalkingStateChangedDelegate OnPlayerTalkingStateChangedDelegate;
	void OnPlayerTalkingStateChanged(TSharedRef<const FUniqueNetId> TalkingPlayerId, bool bIsTalking);

	/*
	 * Draw the most recently killed player if needed
	 *
	 * @return Returns the bottom of the message or 0 if not drawn.
	 */
	float DrawRecentlyKilledPlayer();

	/** Temporary helper for drawing text-in-a-box. */
	void DrawDebugInfoString(const FString& Text, float PosX, float PosY, bool bAlignLeft, bool bAlignTop, const FColor& TextColor);

	/** helper for getting uv coords in normalized top,left, bottom, right format */
	void MakeUV(FCanvasIcon& Icon, FVector2D& UV0, FVector2D& UV1, uint16 U, uint16 V, uint16 UL, uint16 VL);

	/*
	 * Create the chat widget if it doesn't already exist.
	 *
	 * @return		true if the widget was created.
	 */
	bool TryCreateChatWidget();

	/*
	 * Add information string that will be displayed on the hud. They are added as required and rendered together to prevent overlaps 
	 * 
	 * @param InInfoString	InInfoString
	*/
	void AddMatchInfoString(const FCanvasTextItem InfoItem);

	/*
	* Render the info messages.
	*
	* @param YOffset	YOffset from top of canvas to start drawing the messages
	* @param ScaleUI	UI Scale factor
	* @param TextScale	Text scale factor
	*
	* @returns The next Y position to draw any further strings
	*/
	float ShowInfoItems(float YOffset, float TextScale);
};