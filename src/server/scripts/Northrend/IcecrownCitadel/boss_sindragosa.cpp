/*
* Copyright (C) 2009 - 2010 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/*
*Need correct timers
*Need add  Sindragossa fly in fly phase
*/

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "icecrown_citadel.h"

enum Yells
{
    SAY_AGGRO            = -1666071,
    SAY_UNCHAIND_MAGIC   = -1666072,
    SAY_BLISTERING_COLD  = -1666073,
    SAY_BREATH           = -1666074,
    SAY_AIR_PHASE        = -1666075,
    SAY_PHASE_3          = -1666076,
    SAY_KILL_1           = -1666077,
    SAY_KILL_2           = -1666078,
    SAY_BERSERK          = -1666079,
    SAY_DEATH            = -1666080
};

enum Spells
{
    SPELL_FROST_AURA          = 70084,
    SPELL_CLEAVE              = 19983,
    SPELL_TAIL_SMASH          = 71077,
    SPELL_FROST_BREATH        = 69649,
    SPELL_PERMEATING_CHILL    = 70109,
    SPELL_UNCHAINED_MAGIC     = 69762, // io?ii ociaou iaoaieeo ia ioa
    SPELL_ICY_TRIP_PULL       = 70117,
    SPELL_ICY_TRIP_JUMP       = 70122,
    SPELL_BLISTERING_COLD     = 70123,
    SPELL_FROST_BOMB_TRIGGER  = 69846,
    SPELL_FROST_BEACON_EFFECT = 69675,
    SPELL_FROST_BEACON        = 70126,
    SPELL_ICE_TOMB            = 70157,
    SPELL_FROST_BOMB          = 69845,
    SPELL_MYSTIC_BUFFED       = 70128,
    SPELL_ASPHYXATION         = 71665,
    SPELL_FROST_AURA_ADD      = 71387,
    SPELL_FROST_BREATH_ADD    = 71386,
    SPELL_ICY_BLAST           = 71376,

    SPELL_ICY_BLAST_GROUND_10N= 69238,
    SPELL_ICY_BLAST_GROUND_10H= 69628,
    SPELL_ICY_BLAST_GROUND_25N= 71380,
    SPELL_ICY_BLAST_GROUND_25H= 71381,

    SPELL_ICY_BAST_IMPACT_10N = 71377,
    SPELL_ICY_BAST_IMPACT_10H = 69233,
    SPELL_ICY_BAST_IMPACT_25N = 69646,
    SPELL_ICY_BAST_IMPACT_25H = 71377,

    SPELL_BELLOWING_ROAR      = 36922,
    SPELL_CLEAVE_ADD          = 40505,
    SPELL_TAIL_SWEEP          = 71369,
    SPELL_WITHOUT_ANIMATION   = 40031
};

enum ePoints
{
    POINT_PHASE_FLY                = 1,
    POINT_PHASE_NORMAL             = 2,
    POINT_LANDING                  = 3
};

enum eEvents
{
    //Rimefang
    EVENT_FROST_BREATH = 1,
    EVENT_ICY_BLAST,
    EVENT_FLY_PHASE,
    EVENT_GROUND_PHASE,
    //Spinestalker
    EVENT_TAIL_SWEEP,
    EVENT_CLEAVE,
    EVENT_BELLOWING_ROAR
};

enum ePhases 
{
	PHASE_NORMAL				= 0,
	PHASE_FLY					= 1
};

enum eSindragosaActions
{
    ACTION_ICY_BLAST_IMPACT = 1
};
/*
Sindragosa casts spell 69846. Bomb flies down to the mob. When it lands, it explodes.

Position: X: 4360.1 Y: 2510.012 Z: 203.4833 O: 3.141593
Position: X: 4391.1 Y: 2476.4 Z: 203.4833 O: 3.141593
Position: X: 4394.1 Y: 2498.075 Z: 203.4833 O: 3.141593
Position: X: 4408.1 Y: 2466.511 Z: 203.4833 O: 3.141593

Position: X: 4390.1 Y: 2467.817 Z: 203.4833 O: 3.141593
Position: X: 4397.1 Y: 2483.4 Z: 203.4833 O: 3.141593

const Position SpawnLoc[]=
{
    {4523.889f, 2486.907f, 280.249f, 3.155f}, //fly pos
    {4407.439f, 2484.905f, 203.374f, 3.166f}, //center
    {4407.439f, 2484.905f, 230.374f, 3.166f}, //center Z + 30
    {4671.521f, 2481.815f, 343.365f, 3.166f} //spawn pos
};*/
const Position DragonLoc[] = 
{
    {4430.0f, 2460.0f, 203.386f, 3.166f}, //Rimefang landing position
    {4430.0f, 2506.0f, 203.386f, 3.166f}  //Spinestalker landing position
};
class boss_sindragosa : public CreatureScript
{
    public:
        boss_sindragosa() : CreatureScript("boss_sindragosa") { }

        struct boss_sindragosaAI : public BossAI
        {
            boss_sindragosaAI(Creature* creature) : BossAI(creature, DATA_SINDRAGOSA)
            {
                instance = me->GetInstanceScript();
            }

            void Reset()
            {
                uiPhase = 1;

                uiBreathTimer = 15000;
                uiTailSmashTimer = 15000;
                uiBlisteringColdTimer = 30000;
                uiMarkTimer = 25000;
                uiBerserkTimer = 600000;
                uiChangePhaseTimer = 110000;
                uiUnchainedMagicTimer = 12000;
                uiBombTimer = 7000;
                uiCleaveTimer = 5000;
                uiBombCount = 0;

                me->SetFlying(true);
                SetCombatMovement(true);

                bMystic = false;
                bCanSwitch = false;

                if(instance)
                    instance->SetData(DATA_SINDRAGOSA_EVENT, NOT_STARTED);

                if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                    me->GetMotionMaster()->MovementExpired();
            }

            void EnterCombat(Unit* /*who*/)
            {
                if(instance)
                    instance->SetData(DATA_SINDRAGOSA_EVENT, IN_PROGRESS);

                DoCast(me, SPELL_FROST_AURA);
                DoCast(me, SPELL_PERMEATING_CHILL);
                DoScriptText(SAY_AGGRO, me);
            }

            void JustDied(Unit* /*killer*/)
            {
                if (!instance)
                    return;

                DoScriptText(SAY_DEATH, me);

                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_UNCHAINED_MAGIC);
                instance->SetData(DATA_SINDRAGOSA_EVENT, DONE);
                if(instance->GetData(DATA_ALL_YOU_CAN_EAT) == DONE)
                    instance->DoCompleteAchievement(RAID_MODE(ACHIEV_ALL_YOU_CAN_EAT_10,ACHIEV_ALL_YOU_CAN_EAT_25));
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    DoScriptText(RAND(SAY_KILL_1,SAY_KILL_2), me);
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if(type != POINT_MOTION_TYPE)
                    return;

                if(id == POINT_PHASE_FLY)
                    uiPhase = 2;
                else
                {
                    SetCombatMovement(true);
                    me->SetReactState(REACT_AGGRESSIVE);
                    uiPhase = 1;
                }

            }

            void JustReachedHome()
            {
                if (!instance)
                    return;

                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_UNCHAINED_MAGIC);
                instance->SetData(DATA_SINDRAGOSA_EVENT, FAIL);
            }

            void DamageTaken(Unit* /*done_by*/, uint32& /*damage*/)
            {
                if(uiPhase == 1)
                {
                    if(!HealthAbovePct(85) && !bCanSwitch)
                    {
                        DoScriptText(SAY_AIR_PHASE, me);
                        bCanSwitch = true;
                        SetCombatMovement(false);
                        me->GetMotionMaster()->MovePoint(POINT_PHASE_FLY, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 28);
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        me->SetInCombatWithZone();
                    }
                    if(HealthAbovePct(36))
                        return;

                    DoScriptText(SAY_PHASE_3, me);
                    uiPhase = 3;
                }
            }


            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (uiBerserkTimer <= uiDiff)
                {
                    DoScriptText(SAY_BERSERK, me);
                    DoCast(me, SPELL_BERSERK);
                    uiBerserkTimer = 600000;
                } else uiBerserkTimer -= uiDiff;

                if(uiPhase == 1)
                {
                    if(uiUnchainedMagicTimer <= uiDiff)
                    {
                        for (uint8 i = 1; i <= urand(2, 4); ++i)
                        {
                            if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -10.0f, true, -SPELL_UNCHAINED_MAGIC))
                                DoCast(target, SPELL_UNCHAINED_MAGIC);
                        }
                        DoScriptText(SAY_UNCHAIND_MAGIC, me);
                        uiUnchainedMagicTimer = 12000;
                    } else uiUnchainedMagicTimer -= uiDiff;

                    if (uiBreathTimer <= uiDiff)
                    {
                        DoScriptText(SAY_BREATH, me);
                        DoCastVictim(SPELL_FROST_BREATH);
                        uiBreathTimer = 15000;
                    } else uiBreathTimer -= uiDiff;

                    if (uiCleaveTimer <= uiDiff)
                    {
                        DoCastVictim(SPELL_CLEAVE);
                        uiCleaveTimer = 6000;
                    } else uiCleaveTimer -= uiDiff;

                    if (uiTailSmashTimer <= uiDiff)
                    {
                        DoCast(SPELL_TAIL_SMASH);
                        uiTailSmashTimer = 15000;
                    } else uiTailSmashTimer -= uiDiff;

                    if (uiBlisteringColdTimer <= uiDiff)
                    {
                        DoCast(SPELL_ICY_TRIP_PULL);
                        DoCast(SPELL_BLISTERING_COLD);
                        DoScriptText(SAY_BLISTERING_COLD, me);
                        uiBlisteringColdTimer = 30000;
                    } else uiBlisteringColdTimer -= uiDiff;
                }

                if(uiPhase == 2)
                {
                    if (uiMarkTimer < uiDiff)
                    {
                        for (uint8 i = 1; i <= RAID_MODE(2,5,2,5); ++i)
                        {
                            if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true, -SPELL_FROST_BEACON))
                                DoCast(target, SPELL_FROST_BEACON_EFFECT, true);
                        }
                        uiMarkTimer = 25000;
                    } else uiMarkTimer -= uiDiff;

                    if (uiBombTimer <= uiDiff)
                    {
                        if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 150.0f, true))
                            DoCast(target, SPELL_FROST_BOMB);
                        ++uiBombCount;
                        uiBombTimer = 7000;
                    } else uiBombTimer -= uiDiff;

                    if(uiBombCount >= RAID_MODE(4, 8, 4, 8))
                    {
                        uiBombCount = 0;
                        me->GetMotionMaster()->MovePoint(POINT_PHASE_NORMAL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() - 28);
                    }
                }

                if(uiPhase == 3)
                {
                    if (uiMarkTimer < uiDiff)
                    {
                        for (uint8 i = 1; i <= RAID_MODE(2,5,2,5); ++i)
                        {
                            if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true, -SPELL_FROST_BEACON))
                                DoCast(target, SPELL_FROST_BEACON);
                        }
                        uiMarkTimer = 25000;
                    } else uiMarkTimer -= uiDiff;

                    if (uiBreathTimer <= uiDiff)
                    {
                        DoScriptText(SAY_BREATH, me);
                        DoCast(SPELL_FROST_BREATH);
                        uiBreathTimer = 15000;
                    } else uiBreathTimer -= uiDiff;

                    if(!bMystic)
                    {
                       DoCast(me, SPELL_MYSTIC_BUFFED);
                       bMystic = true;
                    }
                }

                if(!bCanSwitch || uiPhase != 1)
                    return;

                if (uiChangePhaseTimer < uiDiff)
                {
                    DoScriptText(SAY_AIR_PHASE, me);
                    uiPhase = 2;
                    SetCombatMovement(false);
                    me->GetMotionMaster()->MovePoint(POINT_PHASE_FLY, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 28);
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->SetInCombatWithZone();
                    uiChangePhaseTimer = 110000;
                } else uiChangePhaseTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* instance;

            uint8 uiPhase;
            uint8 uiBombCount;
            uint32 uiBreathTimer;
            uint32 uiCleaveTimer;
            uint32 uiTailSmashTimer;
            uint32 uiBlisteringColdTimer;
            uint32 uiBerserkTimer;
            uint32 uiMarkTimer;
            uint32 uiChangePhaseTimer;
            uint32 uiUnchainedMagicTimer;
            uint32 uiBombTimer;

            bool bMystic;
            bool bCanSwitch;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_sindragosaAI(creature);
        }
};

class npc_ice_tomb : public CreatureScript
{
    public:
        npc_ice_tomb() : CreatureScript("npc_ice_tomb") { }

        struct npc_ice_tombAI: public Scripted_NoMovementAI
        {
            npc_ice_tombAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                uiTargetGUID = 0;
            }

            void SetGUID(const uint64& guid)
            {
                uiTargetGUID = guid;
            }

            void Reset()
            {
                uiTargetGUID = 0;
            }

            void JustDied(Unit* killer)
            {
                if (Player* IceTomb = ObjectAccessor::GetPlayer(*me, uiTargetGUID))
                {
                    IceTomb->RemoveAurasDueToSpell(SPELL_ICE_TOMB);
                    IceTomb->RemoveAurasDueToSpell(SPELL_ASPHYXATION);
                }
            }

            void KilledUnit(Unit* victim)
            {
                me->Kill(me);
            }

            void UpdateAI(const uint32 /*uiDiff*/)
            {
                if(!uiTargetGUID)
                    return;

                if (Player* IceTomb = ObjectAccessor::GetPlayer(*me, uiTargetGUID))
                    if (!IceTomb->HasAura(SPELL_ICE_TOMB))
                        me->Kill(me);
            }

        private:
            uint64 uiTargetGUID;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_ice_tombAI(creature);
        }
};

class npc_rimefang : public CreatureScript
{
    public:
        npc_rimefang() : CreatureScript("npc_rimefang") { }

        struct npc_rimefangAI: public ScriptedAI
        {
            npc_rimefangAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
                creature->SetVisible(false);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                creature->SetStandState(UNIT_STAND_STATE_SIT);
                originalFaction = creature->getFaction();
            }

            void Reset()
            {
                events.Reset();
                me->SetStandState(UNIT_STAND_STATE_SIT);
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_LAND:
                        //me->GetMotionMaster()->MovementExpired();
                        //me->GetMotionMaster()->Clear();
                        //me->SetDefaultMovementType(IDLE_MOTION_TYPE);
                        //me->GetMotionMaster()->Clear();
                        //me->GetMotionMaster()->Initialize();
                        //me->GetMotionMaster()->MovePoint(POINT_LANDING, DragonLoc[0]);
                        me->SetPhaseMask(1, true); 
                        me->SendMovementFlagUpdate();
                        me->SetVisible(true);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        me->SetStandState(UNIT_STAND_STATE_SIT);
                        break;
                    default:
                        ScriptedAI::DoAction(action);
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_FROST_BREATH, 10000, 0, PHASE_NORMAL);
                events.ScheduleEvent(EVENT_FLY_PHASE, 30000, 0, PHASE_NORMAL);
                events.SetPhase(PHASE_NORMAL);
                me->setFaction(1620); //Become everyone's enemy
                me->SetStandState(UNIT_STAND_STATE_STAND);
                DoCast(me, SPELL_FROST_AURA_ADD);
            }
            void JustReachedHome()
            {
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x01);
                me->SetFlying(false);
                me->setFaction(originalFaction);
                me->SetReactState(REACT_AGGRESSIVE);
                UnsummonSpecificCreaturesNearby(me, CREATURE_ICY_BLAST, 80.0f);
            }
            void JustDied(Unit* /*killer*/)
            {
                me->setFaction(originalFaction);
                if(instance)
                    if(instance->GetData(DATA_SINDRAGOSA_EVENT) != DONE)
                        instance->SetData(DATA_SPAWN, instance->GetData(DATA_SPAWN)+1);
            }
            void MovementInform(uint32 type, uint32 id)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                switch (id)
                {
                    //case POINT_LANDING:
                    //    //me->GetMotionMaster()->MovementExpired();
                    //    //me->StopMoving();
                    //    //me->GetMotionMaster()->Clear();
                    //    //me->SetDefaultMovementType(IDLE_MOTION_TYPE);
                    //    //me->StopMoving();
                    //    //me->GetMotionMaster()->Clear();
                    //    //me->GetMotionMaster()->MoveIdle();
                    //    me->SetReactState(REACT_AGGRESSIVE);
                    //    me->SetFlying(false);
                    //    me->SetStandState(UNIT_STAND_STATE_SIT);
                    //    me->SetHomePosition(DragonLoc[0]);
                    //    me->SetPosition(DragonLoc[0], false);
                    //    me->GetMotionMaster()->MoveTargetedHome();
                    //    break;
                    case POINT_PHASE_FLY:
						events.ScheduleEvent(EVENT_ICY_BLAST, 100, 0, PHASE_FLY);
						events.ScheduleEvent(EVENT_GROUND_PHASE, 15000, 0, PHASE_FLY);
                        break;
                    case POINT_PHASE_NORMAL:
                        me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                        me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x01);
                        me->SetFlying(false);
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Unit *victim = me->SelectVictim())
                            AttackStart(victim);


      //                  me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x01);
						//me->SetFlying(false);
						//SetCombatMovement(true);
						//me->SetReactState(REACT_AGGRESSIVE);
						//me->SetInCombatWithZone();
      //                  if (Unit *victim = me->SelectVictim())
      //                      AttackStart(victim);
                        events.ScheduleEvent(EVENT_FLY_PHASE, 50000, 0, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_FROST_BREATH, 1000, 0, PHASE_NORMAL);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;
                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;
                events.Update(uiDiff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
						//Only happens in ground phase
                        case EVENT_FROST_BREATH:
                            DoCastVictim(SPELL_FROST_BREATH_ADD);
                            events.ScheduleEvent(EVENT_FROST_BREATH, 20000, 0, PHASE_NORMAL);
                            break;
						//Only happens in flying phase
                        case EVENT_ICY_BLAST:
                            if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            {
                                Position posBeacon;
                                pTarget->GetRandomNearPosition(posBeacon, 5.0f);
                                Unit *pBeacon = DoSummon(CREATURE_ICY_BLAST, posBeacon, 60000, TEMPSUMMON_TIMED_DESPAWN);
                                DoCast(pBeacon, SPELL_ICY_BLAST);
                            }
                            //Spam Ice blast while flying
                            events.ScheduleEvent(EVENT_ICY_BLAST, 3000, 0, PHASE_FLY);
                            break;
                        case EVENT_FLY_PHASE:
							events.Reset();
							events.SetPhase(PHASE_FLY);
                            DoStopAttack();
                            me->SetReactState(REACT_PASSIVE);

                            me->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                            me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x01);
                            me->SetFlying(true);

                            //me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x01);
							//me->SetFlying(true);
							//SetCombatMovement(false);
							//me->SetReactState(REACT_PASSIVE);
							//me->AttackStop();
							//me->SetInCombatWithZone();
							me->GetMotionMaster()->MovePoint(POINT_PHASE_FLY, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 28);
                            break;
						case EVENT_GROUND_PHASE:
							events.Reset();
							events.SetPhase(PHASE_NORMAL);
							me->GetMotionMaster()->MovePoint(POINT_PHASE_NORMAL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() - 28);
							break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* instance;
            EventMap events;
            uint32 originalFaction;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_rimefangAI(creature);
        }
};

class npc_spinestalker : public CreatureScript
{
    public:
        npc_spinestalker() : CreatureScript("npc_spinestalker") { }

        struct npc_spinestalkerAI: public ScriptedAI
        {
            npc_spinestalkerAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
                creature->SetVisible(false);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                creature->SetStandState(UNIT_STAND_STATE_SIT);
            }

            void Reset()
            {
                events.Reset();
                me->SetStandState(UNIT_STAND_STATE_SIT);
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_LAND:
                        me->SetPhaseMask(1, true); 
                        me->SendMovementFlagUpdate();
                        me->SetVisible(true);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        me->SetStandState(UNIT_STAND_STATE_SIT);
                        //me->GetMotionMaster()->MovementExpired();
                        //me->GetMotionMaster()->Clear();
                        //me->SetDefaultMovementType(IDLE_MOTION_TYPE);
                        //me->GetMotionMaster()->Clear();
                        //me->GetMotionMaster()->Initialize();
                        //me->GetMotionMaster()->MovePoint(POINT_LANDING, DragonLoc[1]);
                        break;
                    default:
                        ScriptedAI::DoAction(action);
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CLEAVE, 8000);
                events.ScheduleEvent(EVENT_TAIL_SWEEP, 10000);
                events.ScheduleEvent(EVENT_BELLOWING_ROAR, 20000);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                DoCast(me, SPELL_FROST_AURA_ADD);
            }

            void JustDied(Unit* /*killer*/)
            {
                if(instance->GetData(DATA_SINDRAGOSA_EVENT) != DONE)
                    instance->SetData(DATA_SPAWN, instance->GetData(DATA_SPAWN)+1);
            }

            //void MovementInform(uint32 type, uint32 id)
            //{
            //    if (type != POINT_MOTION_TYPE)
            //        return;

            //    switch (id)
            //    {
            //        case POINT_LANDING:
            //            //me->GetMotionMaster()->MovementExpired();
            //            //me->StopMoving();
            //            //me->GetMotionMaster()->Clear();
            //            //me->SetDefaultMovementType(IDLE_MOTION_TYPE);
            //            //me->StopMoving();
            //            //me->GetMotionMaster()->Clear();
            //            //me->GetMotionMaster()->MoveIdle();
            //            me->SetReactState(REACT_AGGRESSIVE);
            //            me->SetFlying(false);
            //            me->SetStandState(UNIT_STAND_STATE_SIT);
            //            me->SetHomePosition(DragonLoc[1]);
            //            me->SetPosition(DragonLoc[1], true);
            //            me->NearTeleportTo(DragonLoc[1].GetPositionX(), DragonLoc[1].GetPositionY(), DragonLoc[1].GetPositionZ(), DragonLoc[1].GetOrientation(), true);
            //            me->GetMotionMaster()->MoveTargetedHome();
            //            break;
            //    }
            //}

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;
                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;
                events.Update(uiDiff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BELLOWING_ROAR:
                        {
                            DoCastAOE(SPELL_BELLOWING_ROAR);
                            events.ScheduleEvent(EVENT_BELLOWING_ROAR, 30000);
                            break;
                        }
                        case EVENT_CLEAVE:
                        {
                            DoCastVictim(SPELL_CLEAVE_ADD);
                            events.ScheduleEvent(EVENT_CLEAVE, 5000);
                            break;
                        }
                        case EVENT_TAIL_SWEEP:
                        {
                            DoCast(SPELL_TAIL_SWEEP);
                            events.ScheduleEvent(EVENT_TAIL_SWEEP, 20000);
                            break;
                        }
                    }
                }
                DoMeleeAttackIfReady();
            }
        private:
            InstanceScript* instance;
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_spinestalkerAI(creature);
        }
};

class spell_sindragosa_ice_tomb : public SpellScriptLoader
{
    public:
        spell_sindragosa_ice_tomb() : SpellScriptLoader("spell_sindragosa_ice_tomb") { } //70157


        class spell_sindragosa_ice_tomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sindragosa_ice_tomb_AuraScript)

            void OnPeriodic(AuraEffect const* aurEff)
            {
                GetCaster()->CastSpell(GetTarget(), SPELL_ICE_TOMB, true);
                GetCaster()->CastSpell(GetTarget(), SPELL_ASPHYXATION, true);
                Creature* tomb = GetCaster()->SummonCreature(CREATURE_ICE_TOMB, GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
                if(tomb)
                {
                    tomb->CastSpell(tomb, SPELL_WITHOUT_ANIMATION, true);
                    tomb->AI()->SetGUID(GetTarget()->GetGUID());
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sindragosa_ice_tomb_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sindragosa_ice_tomb_AuraScript();
        }
};

class spell_sindragosa_mystic_buffet : public SpellScriptLoader
{
    public:
        spell_sindragosa_mystic_buffet() : SpellScriptLoader("spell_sindragosa_mystic_buffet") { } //70127


        class spell_sindragosa_mystic_buffet_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sindragosa_mystic_buffet_AuraScript)

            void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (InstanceScript* instance = GetOwner()->GetInstanceScript())
                    if(GetStackAmount() >= 5)
                        instance->SetData(DATA_ALL_YOU_CAN_EAT, FAIL);
                    else
                        instance->SetData(DATA_ALL_YOU_CAN_EAT, DONE);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_sindragosa_mystic_buffet_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sindragosa_mystic_buffet_AuraScript();
        }
};

class spell_sindragosa_unchained_magic : public SpellScriptLoader
{
    public:
        spell_sindragosa_unchained_magic() : SpellScriptLoader("spell_sindragosa_unchained_magic") { } //69766


        class spell_sindragosa_unchained_magic_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sindragosa_unchained_magic_AuraScript)

            void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                int32 damage = (GetStackAmount() * 2000);
                GetTarget()->CastCustomSpell(71044, SPELLVALUE_BASE_POINT0, damage, GetTarget(), true, NULL, aurEff, GetCasterGUID());
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_sindragosa_unchained_magic_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sindragosa_unchained_magic_AuraScript();
        }
};

class spell_sindragosa_ice_tomb_effect : public SpellScriptLoader
{
    public:
        spell_sindragosa_ice_tomb_effect() : SpellScriptLoader("spell_sindragosa_ice_tomb_effect") { }


        class spell_sindragosa_ice_tomb_effect_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sindragosa_ice_tomb_effect_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!(GetHitUnit() && GetHitUnit()->isAlive() && GetCaster()))
                    return;

                if (GetHitUnit()->GetTypeId() == TYPEID_PLAYER)
                    GetCaster()->CastSpell(GetHitUnit(), SPELL_FROST_BEACON, true);
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_sindragosa_ice_tomb_effect_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sindragosa_ice_tomb_effect_SpellScript();
        }
};

class spell_sindragosa_blistering_cold : public SpellScriptLoader
{
    public:
        spell_sindragosa_blistering_cold() : SpellScriptLoader("spell_sindragosa_blistering_cold") { }


        class spell_sindragosa_blistering_cold_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sindragosa_blistering_cold_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!(GetHitUnit() && GetHitUnit()->isAlive() && GetCaster()))
                    return;

                GetHitUnit()->CastSpell(GetCaster(), SPELL_ICY_TRIP_JUMP, true);
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_sindragosa_blistering_cold_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sindragosa_blistering_cold_SpellScript();
        }
};

class npc_icc_frostwing_mob : public CreatureScript
{
    public:
        npc_icc_frostwing_mob() : CreatureScript("npc_icc_frostwing_mob") { }

        struct npc_icc_frostwing_mobAI : public ScriptedAI
        {
            npc_icc_frostwing_mobAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }
            void JustRespawned()
            {
                if(pInstance && pInstance->GetData(DATA_SINDRAGOSA_EVENT) != DONE)
                {
                    uint32 dataType = (me->GetHomePosition().GetPositionY() < 2480.0f) ? DATA_FROSTWING_MOB_RIGHT : DATA_FROSTWING_MOB_LEFT;
                    pInstance->SetData(dataType, pInstance->GetData(dataType)+1);
                }
            }
            void JustDied(Unit* /*killer*/)
            {
                uint32 dataType = (me->GetHomePosition().GetPositionY() < 2480.0f) ? DATA_FROSTWING_MOB_RIGHT : DATA_FROSTWING_MOB_LEFT;
                pInstance->SetData(dataType, pInstance->GetData(dataType)-1);
            }
        private:
            InstanceScript *pInstance;
        };
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_frostwing_mobAI(pCreature);
        }
};

class npc_icc_icy_blast : public CreatureScript
{
    public:
        npc_icc_icy_blast() : CreatureScript("npc_icc_icy_blast") { }

        struct npc_icc_icy_blastAI : public ScriptedAI
        {
            npc_icc_icy_blastAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                bAlreadyHit = false;
            }
            void Reset()
            {
                me->CastSpell(me, 65686, true); //Just for visual aura
            }
            void DamageTaken(Unit* attacker, uint32& damage)
            {
                damage = 0;
                me->SetHealth(me->GetMaxHealth());
            }
            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_ICY_BLAST_IMPACT:
                        me->RemoveAurasDueToSpell(65686); //Just for visual aura
                        DoCast(me, RAID_MODE<uint32>(SPELL_ICY_BLAST_GROUND_10N, SPELL_ICY_BLAST_GROUND_25N, SPELL_ICY_BLAST_GROUND_10H, SPELL_ICY_BLAST_GROUND_25H));
                        break;
                }
            }
            // Called when hit by a spell
            void SpellHit(Unit*, const SpellEntry* sp) 
            {
                if (bAlreadyHit) 
                    return;
                if (!sp || sp->Id != SPELL_ICY_BLAST)
                    return;
                bAlreadyHit = true;
                DoAction(ACTION_ICY_BLAST_IMPACT);
            }
        private:
            InstanceScript *pInstance;
            bool bAlreadyHit;
        };
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_icy_blastAI(pCreature);
        }
};
class spell_icy_blast : public SpellScriptLoader
{
    public:
        spell_icy_blast() : SpellScriptLoader("spell_icc_icy_blast") { }


        class spell_icy_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_icy_blast_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                uint32 effVal = uint32(GetEffectValue());
                PreventHitDefaultEffect(effIndex);
                if (!(GetHitUnit() && GetHitUnit()->isAlive() && GetHitUnit()->GetEntry() == CREATURE_ICY_BLAST))
                    return;
                if (Creature *pIcyBlast = GetHitUnit()->ToCreature())
                    pIcyBlast->AI()->DoAction(ACTION_ICY_BLAST_IMPACT);
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_icy_blast_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_TRIGGER_MISSILE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_icy_blast_SpellScript();
        }
};


void AddSC_boss_sindragosa()
{
    new boss_sindragosa();
    new npc_spinestalker();
    new npc_rimefang();
    new npc_ice_tomb();
    new spell_sindragosa_ice_tomb();
    new spell_sindragosa_mystic_buffet(); //for achievement
    new spell_sindragosa_unchained_magic();
    new spell_sindragosa_ice_tomb_effect();
    new spell_sindragosa_blistering_cold();
    new spell_icy_blast();
    new npc_icc_frostwing_mob();
    new npc_icc_icy_blast();
}