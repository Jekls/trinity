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

#include "ScriptPCH.h"
#include "icecrown_citadel.h"

enum Yells
{
    SAY_AGGRO       = -1666063,
    SAY_BELOW_25    = -1666066,
    SAY_ABOVE_75    = -1666065,
    SAY_DEATH       = -1666067,
    SAY_PDEATH      = -1666068,
    SAY_END         = -1666070,
    SAY_FAILURES    = -1666069,
    SAY_OPEN_PORTAL = -1666064
};

enum Spells
{
    SPELL_FEIGN_DEATH                   = 71598,
    SPELL_CORRUPTION    = 70904,
    SPELL_DREAM_SLIP    = 71196,
    SPELL_RAGE          = 71189,
    SPELL_COLUMN_PRE    = 70704,
    SPELL_COLUMN_EFFECT_10N = 70702,
    SPELL_COLUMN_EFFECT_10H_25N = 71746,
    SPELL_COLUMN_EFFECT_25H = 72020,
   
    SPELL_SUMMON_ROT_WORMS_AURA = 70675,
    SPELL_SUMMON_ROT_WORM_VISUAL = 70668,

    SPELL_DREAM_STATE   = 70766,
    SPELL_VIGOR         = 70873,
    SPELL_TWISTED_NIGHTMARES = 71941,
    SPELL_CLOUD_VISUAL  = 70876,
    SPELL_PORTAL_N_PRE  = 71301,
    SPELL_PORTAL_N_NPC  = 71305,
    SPELL_PORTAL_H_PRE  = 71977,
    SPELL_PORTAL_H_NPC  = 71987,
    SPELL_SUMMON_PORTAL_TO_DREAM = 72482,
    SPELL_DREAM_PORTAL_VISUAL = 71304,
    SPELL_DREAM_PORTAL_VISUAL_2 = 70763,

    SPELL_COPY_DAMAGE                   = 71948, 
    //SPELL_SUMMON_SUPPRESSOR_PERIODIC    = 70912,
    //SPELL_SUMMON_FIRE_SKELETON_PERIODIC = 70913,
    //SPELL_SUMMON_ZOMBIE_PERIODIC        = 70914,
    //SPELL_SUMMON_ABOMINATION_PERIODIC   = 70915,
    //SPELL_SUMMON_ARCHMAGE_PERIODIC      = 70916,
    //SPELL_SUMMON_SUPPRESSOR             = 70935,

    SPEEL_CLEAR_AURA                    = 75863,
    SPELL_CANCEL_ALL_AURAS              = 71721, 

    SPELL_NIGHTMARE_DAMAGE              = 71946,

    //Blistering Zombie spells
    SPELL_ACID_BURST_10N                = 70744,
    SPELL_ACID_BURST_10H                = 72017,
    SPELL_ACID_BURST_25N                = 71733,
    SPELL_ACID_BURST_25H                = 72018,

    SPELL_CORROSION_10N                 = 70751,
    SPELL_CORROSION_10H                 = 71738,
    SPELL_CORROSION_25N                 = 72021,
    SPELL_CORROSION_25H                 = 72022,
    //Gluttonous Abomination spell
    SPELL_GUT_SPRAY_10N                 = 70633,
    SPELL_GUT_SPRAY_10H                 = 72025,
    SPELL_GUT_SPRAY_25N                 = 71283,
    SPELL_GUT_SPRAY_25H                 = 72026,

    SPELL_FLESH_ROT_10N                 = 72963,
    SPELL_FLESH_ROT_10H                 = 72964,
    SPELL_FLESH_ROT_25N                 = 72965,
    SPELL_FLESH_ROT_25H                 = 72966,
    //Risen Archmage spells
    SPELL_FROSTBOLT_VOLLEY              = 70759,
    SPELL_SUMMON_MANA_VOID              = 71179,

    SPELL_FIREBALL                      = 70754,
    SPELL_LAY_WASTE                     = 69325,
    SPELL_SUPPRESSION                   = 70588
};

enum eEvents
{
    EVENT_SUMMON_DREAM_CLOUD        = 1,
    EVENT_DESPAWN                   = 3,
    EVENT_DESPAWN_AND_FAIL_ACHIEVEMENT = 20,
    //Events played when boss is healed up to 100%
    EVENT_BERSERK                   = 4,
    EVENT_EVADE_TO_DREAM_SLIP       = 5,

    //Adds
    EVENT_SUMMON_ARCHMAGE           = 8,
    EVENT_SUMMON_ZOMBIE             = 17,
    EVENT_SUMMON_ABOMINATION        = 18,
    EVENT_SUMMON_SUPPRESSOR          = 9,
    EVENT_SUMMON_BLAZING_SKELETON   = 10,
    EVENT_CAST_COLUMN_OF_FROST      = 11,
    EVENT_HASTEN_SUMMON_TIMER       = 12,

    //Portals
    EVENT_SUMMON_PORTALS_TO_DREAM   = 2,
    EVENT_OPEN_PORTAL_TO_DREAM      = 6,
    EVENT_EXPLODE                   = 13,
    EVENT_CLOUD_EMULATE_DESPAWN     = 14,
    EVENT_CLOUD_EMULATE_RESPAWN     = 15,
    EVENT_INTRO                     = 7,

    EVENT_CHECK_WIPE                = 16,
    EVENT_CAST_ROT_WORM_SPAWN_ANIMATION = 19,

    EVENT_GUT_SPRAY                 = 21,
    EVENT_ENABLE_CASTING            = 22, 
    EVENT_FROSTBOLT_VOLLEY          = 23,
    EVENT_SUMMON_MANA_VOID          = 24,
    EVENT_CAST_SUPPRESSION          = 25,

    EVENT_CAST_FIREBALL             = 26,
    EVENT_CAST_LAY_WASTE            = 27
};
enum eValithriaData
{
    DATA_INSTANCE_DIFFICULTY = 1,
    DATA_SUMMONED_LAST_PORTALS = 2
};
enum eActions
{
    ACTION_WIPE = 1
};
#define FACTION_STORMWIND 11
#define FACTION_ORGRIMMAR 1612

const Position Pos[] =
{
    {4239.579102f, 2566.753418f, 364.868439f, 0.0f}, //normal 0,1
    {4240.688477f, 2405.794678f, 364.868591f, 0.0f}, // normal
    {4165.112305f, 2405.872559f, 364.872925f, 0.0f}, //2,3
    {4166.216797f, 2564.197266f, 364.873047f, 0.0f}
};

void Cleanup(Creature *me, InstanceScript *instance, float radius)
{
    //Despawn heroic mode-specific mobs
    UnsummonSpecificCreaturesNearby(me, CREATURE_PORTAL_HEROIC_MODE_PRE, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_PORTAL_HEROIC_MODE_NPC, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_NIGHTMARE_CLOUD, radius);
    
    //Despawn normal mode-specific mobs
    UnsummonSpecificCreaturesNearby(me, CREATURE_PORTAL_NORMAL_MODE_PRE, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_PORTAL_NORMAL_MODE_NPC, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_DREAM_CLOUD, radius);

    UnsummonSpecificCreaturesNearby(me, CREATURE_ZOMBIE, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_SKELETON, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_ARCHMAGE, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_SUPPRESSOR, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_ABOMINATION, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_ROT_WORM, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_COLUMN_OF_FROST, radius);
    UnsummonSpecificCreaturesNearby(me, CREATURE_MANA_VOID, radius);

    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_VIGOR);
    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWISTED_NIGHTMARES);
    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DREAM_STATE);
    instance->DoRemoveAurasDueToSpellOnPlayers(((ScriptedAI*)me->AI())->RAID_MODE<uint32>(SPELL_ACID_BURST_10N, SPELL_ACID_BURST_25N, SPELL_ACID_BURST_10H, SPELL_ACID_BURST_25H));
    instance->DoRemoveAurasDueToSpellOnPlayers(((ScriptedAI*)me->AI())->RAID_MODE<uint32>(SPELL_CORROSION_10N, SPELL_CORROSION_25N, SPELL_CORROSION_10H, SPELL_CORROSION_25H));
    instance->DoRemoveAurasDueToSpellOnPlayers(((ScriptedAI*)me->AI())->RAID_MODE<uint32>(SPELL_FLESH_ROT_10N, SPELL_FLESH_ROT_25N, SPELL_FLESH_ROT_10H, SPELL_FLESH_ROT_25H));
}


class boss_valithria : public CreatureScript
{
    public:
        boss_valithria() : CreatureScript("boss_valithria") { }

        struct boss_valithriaAI : public BossAI
        {
            boss_valithriaAI(Creature* pCreature) : BossAI(pCreature, DATA_VALITHRIA_DREAMWALKER)
            {
                //Make Valithria immune to column of frost in case it's spawned near her
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->SetSpeed(MOVE_RUN, 0.0f, true);
                me->SetSpeed(MOVE_WALK, 0.0f, true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_9); // 3.0.3 - makes you unable to attack everything
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);

                Map::PlayerList const &players = me->GetMap()->GetPlayers();
                uint32 TeamInInstance = 0;
                if (!players.isEmpty())
                {
                    if (Player* pPlayer = players.begin()->getSource())
                        TeamInInstance = pPlayer->GetTeam();
                }
                if (TeamInInstance == ALLIANCE)
                    me->setFaction(FACTION_STORMWIND);
                else
                    me->setFaction(FACTION_ORGRIMMAR);
            }

            void JustDied(Unit* killer)
            {
                me->Respawn();
                DoCast(me, SPELL_CORRUPTION);
                DoAction(ACTION_WIPE);
            }

            void JustRespawned()
            {
                me->SetHealth(me->GetMaxHealth() / 2);
            }

            void Reset()
            {
                events.Reset();
                DoCast(me, SPEEL_CLEAR_AURA);
                DoCast(me, SPELL_CORRUPTION);
                me->SetHealth(uint32(me->GetMaxHealth() / 2));

                bIntro = false;
                bEnd = false;
                bAboveHP = false;
                bBelowHP = false;
                bSummonedLastPortals = false;
                DoCast(SPELL_COPY_DAMAGE);
                if(SpellEntry* copy = GET_SPELL(SPELL_COPY_DAMAGE))
                    copy->Targets = 18;

            }
            void DoAction(const int32 action)
            {
                if (action == EVENT_INTRO)
                {
                    Reset();
                    if (Creature* combatTrigger = me->GetCreature(*me, instance->GetData64(DATA_VALITHRIA_COMBAT_TRIGGER)))
                        me->getThreatManager().addThreat(combatTrigger, 1.0f);
                    
                    me->GetInstanceScript()->SetData(DATA_PORTAL_JOCKEY_ACHIEVEMENT, (uint32)true);
                    if (IsHeroic())
                        DoCast(me, SPELL_NIGHTMARE_DAMAGE);
                    events.ScheduleEvent(EVENT_INTRO, 10000);
                }
                if (action == ACTION_WIPE)
                {
                    Reset();
                    events.Reset();
                    DoScriptText(SAY_FAILURES, me);
                    DoCast(me, SPELL_RAGE);
                    instance->SetData(DATA_VALITHRIA_DREAMWALKER_EVENT, FAIL);
                    Cleanup(me, instance, 100.0f);
                    if (Creature* combatTrigger = me->GetCreature(*me, instance->GetData64(DATA_VALITHRIA_COMBAT_TRIGGER)))
                        combatTrigger->AI()->EnterEvadeMode();
                    me->RemoveAllAuras();
                    DoCast(me, SPELL_CORRUPTION);
                    me->SetHealth(uint32(me->GetMaxHealth() / 2));
                    EnterEvadeMode();
                    return;
                }
            }
 
            uint32 GetData(uint32 id)
            {
                switch (id)
                {
                    case DATA_INSTANCE_DIFFICULTY:
                        return RAID_MODE(10, 25, 10, 25);
                    case DATA_SUMMONED_LAST_PORTALS:
                        return bSummonedLastPortals;
                }
                return BossAI::GetData(id);
            }

            void CheckHealth()
            {
                //Prevent healing while encounter isn't in progress
                if (instance->GetData(DATA_VALITHRIA_DREAMWALKER_EVENT) != IN_PROGRESS)
                {
                    me->SetHealth(uint32(me->GetMaxHealth() / 2));
                    return;
                }
                switch (instance->GetData(DATA_VALITHRIA_DREAMWALKER_EVENT))
                {
                    case DONE:
                        return;
                    case NOT_STARTED:
                    {
                        //Disallow healing while encounter isn't in progress
                        if (Creature* combatTrigger = me->GetCreature(*me, instance->GetData64(DATA_VALITHRIA_COMBAT_TRIGGER)))
                            combatTrigger->AI()->EnterEvadeMode();
                        break;
                    }
                    default:
                        break;
                }
                if (HealthBelowPct(2))
                {
                    DoAction(ACTION_WIPE);
                    return;
                }
                if (!bAboveHP && HealthAbovePct(74))
                {
                    DoScriptText(SAY_ABOVE_75, me);
                    //Need to increase her in size
                    bAboveHP = true;
                    bBelowHP = false;
                }
                if (!bBelowHP && HealthBelowPct(26))
                {
                    DoScriptText(SAY_BELOW_25, me);
                    //Need to decrease her in size
                    bBelowHP = true;
                    bAboveHP = false;
                }
                if (bSummonedLastPortals && HealthBelowPct(91))
                {
                    //Reset summoning last 3 portals event
                    bSummonedLastPortals = false;
                }
                if (!bSummonedLastPortals && HealthAbovePct(94))
                {
                    bSummonedLastPortals = true;
                    //It's very much worth noting that if Dreamwalker spawns 3 portals when almost healed to 100%
                    for (uint8 i = 0; i < 3; ++i)
                        DoCast(RAID_MODE(SPELL_PORTAL_N_PRE,SPELL_PORTAL_N_PRE,SPELL_PORTAL_H_PRE,SPELL_PORTAL_H_PRE));
                }
                if (!bEnd && HealthAbovePct(99))
                {
                    DoScriptText(SAY_END, me);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->SetReactState(REACT_PASSIVE);
                    DoCast(me, SPELL_CANCEL_ALL_AURAS);
                    me->RemoveAurasDueToSpell(SPELL_CORRUPTION);
                    bEnd = true;
                    events.Reset();
                    events.ScheduleEvent(EVENT_BERSERK, 1000);
                    if (instance->GetData(DATA_PORTAL_JOCKEY_ACHIEVEMENT))
                        instance->DoCompleteAchievement(RAID_MODE(ACHIEV_PORTAL_JOCKEY_10, ACHIEV_PORTAL_JOCKEY_25, ACHIEV_PORTAL_JOCKEY_10, ACHIEV_PORTAL_JOCKEY_25)); 
                }
            }

            void DamageTaken(Unit* /*done_by*/, uint32& /*damage*/)
            {
                CheckHealth();
            }

            void HealReceived(Unit* /*done_by*/, uint32& /*addhealth*/)
            {
                CheckHealth();
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_INTRO:
                        {
                            DoScriptText(SAY_AGGRO, me);
                            //events.ScheduleEvent(EVENT_SUMMON_ADDS, 10000);
                            events.ScheduleEvent(EVENT_SUMMON_PORTALS_TO_DREAM, 35000);
                            break;
                        }
                        case EVENT_SUMMON_PORTALS_TO_DREAM:
                        {
                            DoScriptText(SAY_OPEN_PORTAL, me);
                            //DoCast(SPELL_SUMMON_PORTAL_TO_DREAM);
                            //Need to check, maybe, this isn't required
                            for(uint8 p = 0; p < RAID_MODE<uint8>(3, 8, 3, 8); ++p)
                                DoCast(RAID_MODE(SPELL_PORTAL_N_PRE,SPELL_PORTAL_N_PRE,SPELL_PORTAL_H_PRE,SPELL_PORTAL_H_PRE));
                            if (Creature* valithriaAlternative = Unit::GetCreature(*me, instance->GetData64(DATA_VALITHRIA_ALTERNATIVE)))
                                valithriaAlternative->AI()->DoAction(EVENT_SUMMON_DREAM_CLOUD);
                            events.ScheduleEvent(EVENT_SUMMON_PORTALS_TO_DREAM, 50000);
                            break;
                        }
                        case EVENT_BERSERK:
                        {
                            DoCast(me, SPELL_RAGE);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            events.ScheduleEvent(EVENT_EVADE_TO_DREAM_SLIP, 6000);
                            break;
                        }
                        case EVENT_EVADE_TO_DREAM_SLIP:
                        {
                            DoCast(SPELL_DREAM_SLIP);
                            events.ScheduleEvent(EVENT_DESPAWN, 1000);
                            break;
                        }
                        case EVENT_DESPAWN:
                        {
                            Cleanup(me, instance, 100.0f);
                            instance->SetData(DATA_VALITHRIA_DREAMWALKER_EVENT, DONE);
                            if (Creature* combatTrigger = me->GetCreature(*me, instance->GetData64(DATA_VALITHRIA_COMBAT_TRIGGER)))
                                combatTrigger->DespawnOrUnsummon();
                            me->DespawnOrUnsummon();
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

        private:

            bool bIntro;
            bool bEnd;
            bool bAboveHP;
            bool bBelowHP;
            bool bSummonedLastPortals;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_valithriaAI(pCreature);
        }
};

//Dream related NCPs and spells
class npc_valithria_alternative : public CreatureScript
{
    public:
        npc_valithria_alternative() : CreatureScript("npc_valithria_alternative") { }

        struct npc_valithria_alternativeAI : public ScriptedAI
        {
            npc_valithria_alternativeAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                numberOfClouds = RAID_MODE<uint8>(15, 50, 15, 50);
            }

            void Reset()
            {
                events.Reset();
                me->SetPhaseMask(16, true);
                me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY);
                me->SendMovementFlagUpdate();
                me->SetFlying(true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //events.ScheduleEvent(EVENT_SUMMON_DREAM_CLOUD, 15000);
                me->GetPosition(x,y,z);
                bAlreadySummonedClouds = false;
            }
            void DoAction(const int32 action)
            {
                //Clouds do not respawn in heroic mode
                if (action == EVENT_SUMMON_DREAM_CLOUD && !(IsHeroic() && bAlreadySummonedClouds))
                {
                    bAlreadySummonedClouds = true;
                    const uint32 cloudEntry = IsHeroic() ? CREATURE_NIGHTMARE_CLOUD : CREATURE_DREAM_CLOUD;
                    UnsummonSpecificCreaturesNearby(me, cloudEntry, 80.0f);
                    float angle, summonX, summonY, summonZ, distMin = 20.0f, distMax = 35.0f, zVariation = 15.0f, summonDist;
                    //Summon Dream clouds in a circle pattern, but randomize their positions a little (random angle and random Z coordinate)
                    for(uint8 i = 0; i <= numberOfClouds; ++i) //need correct count
                    {
                        //angle = (float)rand_norm() * static_cast<float>(2 * M_PI);
                        //Distribute portals evenly around the boss, with a little angle variation
                        angle = static_cast<float>(2 * M_PI) * i / numberOfClouds + (float)rand_norm() * 0.07;
                        summonDist = distMin + (distMax - distMin) * (float)rand_norm();
                        summonX = x + summonDist * cos(angle);
                        summonY = y + summonDist * sin(angle);
                        summonZ = z + (float)rand_norm() * zVariation - zVariation / 2.0f;
                        //Trinity::NormalizeMapCoord(summonX);
                        //Trinity::NormalizeMapCoord(summonY);
                        me->SummonCreature(cloudEntry, summonX, summonY, summonZ, 0, TEMPSUMMON_TIMED_DESPAWN, IsHeroic() ? 600000 : 50000);
                    }
                }
            }

        private:
            InstanceScript* pInstance;
            bool bAlreadySummonedClouds;
            float x, y, z;
            uint8 numberOfClouds;
            EventMap events;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_valithria_alternativeAI(pCreature);
        }
}; 

class npc_dreamportal_icc : public CreatureScript
{
    public:
        npc_dreamportal_icc() : CreatureScript("npc_dreamportal_icc") { }

        struct npc_dreamportal_iccAI : public Scripted_NoMovementAI
        {
            npc_dreamportal_iccAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                me->SetSpeed(MOVE_WALK, 0.0f);
                me->SetSpeed(MOVE_RUN, 0.0f);
                me->SetReactState(REACT_PASSIVE);
                events.Reset();
                if (Creature* valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER)))
                    if (valithria->GetAI()->GetData(DATA_SUMMONED_LAST_PORTALS))
                        //Last 3 portals should be opened almost immediately after they were summoned
                        events.ScheduleEvent(EVENT_OPEN_PORTAL_TO_DREAM, 1000);
                    else
                        events.ScheduleEvent(EVENT_OPEN_PORTAL_TO_DREAM, 15000);
            }
            void DoAction(const int32 action)
            {
                if (action == EVENT_SPELLCLICK)
                    events.ScheduleEvent(EVENT_DESPAWN, 100);
            }
            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_OPEN_PORTAL_TO_DREAM:
                        {
                            if(me->GetEntry() == CREATURE_PORTAL_NORMAL_MODE_PRE)
                            {
                                me->UpdateEntry(CREATURE_PORTAL_NORMAL_MODE_NPC);
                                if (urand(0, 1))
                                    DoCast(me, SPELL_DREAM_PORTAL_VISUAL);
                                else
                                    DoCast(me, SPELL_DREAM_PORTAL_VISUAL_2);
                            }
                            else
                                if(me->GetEntry() == CREATURE_PORTAL_HEROIC_MODE_PRE)
                                {
                                    me->UpdateEntry(CREATURE_PORTAL_HEROIC_MODE_NPC);
                                    if (urand(0, 1))
                                        DoCast(me, SPELL_DREAM_PORTAL_VISUAL);
                                    else
                                        DoCast(me, SPELL_DREAM_PORTAL_VISUAL_2);
                                }
                            events.ScheduleEvent(EVENT_DESPAWN_AND_FAIL_ACHIEVEMENT, 15000);
                            break;
                        }
                        case EVENT_DESPAWN_AND_FAIL_ACHIEVEMENT:
                        {
                            me->GetInstanceScript()->SetData(DATA_PORTAL_JOCKEY_ACHIEVEMENT, (uint32)false);
                            me->DespawnOrUnsummon();
                            break;
                        }
                        case EVENT_DESPAWN:
                        {
                            me->DespawnOrUnsummon();
                            break;
                        }
                        default:
                            break;
                    }
                }
                

            }

        private:
            EventMap events;
            uint32 m_uiChangeTimer;
            InstanceScript *pInstance;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_dreamportal_iccAI(pCreature);
        }
};

class npc_dreamcloud_icc : public CreatureScript 
{
    public:
        npc_dreamcloud_icc() : CreatureScript("npc_dreamcloud_icc") { }

        struct npc_dreamcloud_iccAI : public ScriptedAI
        {
            npc_dreamcloud_iccAI(Creature* pCreature) : ScriptedAI(pCreature) { }

            void Reset()
            {
                canApplyBuff = true;
                events.Reset();
                me->SetPhaseMask(16, true);
                DoCast(SPELL_CLOUD_VISUAL);
                me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY);
                me->SendMovementFlagUpdate();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_AGGRESSIVE);
            }

            void MoveInLineOfSight(Unit *who)
            {
                if (canApplyBuff && me->IsWithinDistInMap(who, 5.0f, true) && who->GetTypeId() == TYPEID_PLAYER)
                {
                    canApplyBuff = false;
                    //Cloud will explode in about 1-2 seconds after player touch it
                    events.ScheduleEvent(EVENT_EXPLODE, 1500);
                }
                ScriptedAI::MoveInLineOfSight(who);
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_EXPLODE:
                        {
                            //Apply buff to player
                            const uint32 spellId = IsHeroic() ? SPELL_TWISTED_NIGHTMARES : SPELL_VIGOR;
                            //Apply buff only if player is within 5 feet of the cloud
                            DoCast(me, spellId, true);

                            //Just show explode animation effect
                            events.ScheduleEvent(EVENT_CLOUD_EMULATE_DESPAWN, 2000);
                            break;
                        }
                        case EVENT_CLOUD_EMULATE_DESPAWN:
                        {
                            me->SetVisible(false);
                            //In normal mode, the clouds have a very fast respawn so you won�t run the risk of running out of them. 
                            if (!IsHeroic())
                                events.ScheduleEvent(EVENT_CLOUD_EMULATE_RESPAWN, 7000);
                            break;
                        }
                        case EVENT_CLOUD_EMULATE_RESPAWN:
                        {
                            me->SetVisible(true);
                            canApplyBuff = true;
                        }
                        default:
                            break;
                    }
                }
            }
        private:
            EventMap events;
            bool canApplyBuff;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_dreamcloud_iccAI(pCreature);
        }
};

class spell_valithria_summon_portal : public SpellScriptLoader
{
    public:
        spell_valithria_summon_portal() : SpellScriptLoader("spell_valithria_summon_portal") { }

        class spell_valithria_summon_portal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_valithria_summon_portal_SpellScript);

            void ChangeSummonPos(SpellEffIndex /*effIndex*/)
            {
                if (Creature *valithria = GetCaster()->ToCreature())
                {
                    uint32 instanceDifficulty = valithria->GetAI()->GetData(DATA_INSTANCE_DIFFICULTY);
                    float x, y, distMin = 15.0f, distMax = 30.0f;
                    valithria->GetPosition(x, y);
                    float maxAngle = ((instanceDifficulty == 25) ?  static_cast<float>(2 * M_PI) :  static_cast<float>(M_PI));
                    //Decrease ange by 90 degreese because portals should be spawned in front of boss in 10-man modes
                    float angle = (float)rand_norm() * maxAngle - static_cast<float>(M_PI) / 2.0f;
                    float summonDist = distMin + (distMax - distMin) * (float)rand_norm();
                    float summonX = x + summonDist * cos(angle);
                    float summonY = y + summonDist * sin(angle);

                    WorldLocation* summonPos = GetTargetDest();
                    summonPos->Relocate(summonX, summonY); 
                }
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_valithria_summon_portal_SpellScript::ChangeSummonPos, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_valithria_summon_portal_SpellScript();
        }
};

class spell_valithria_vigor : public SpellScriptLoader
{
    public:
        spell_valithria_vigor() : SpellScriptLoader("spell_valithria_vigor") { }

        class spell_valithria_vigor_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_valithria_vigor_SpellScript);

            bool Load()
            {
                playersAuraStacks.clear();
                return true;
            }

            void EnsureThatAurasStack()
            {
                if (!(GetHitUnit() && GetHitUnit()->isAlive()))
                    return;
                if (GetHitUnit()->GetGUID() == GetCaster()->GetGUID())
                    return;

                if (Unit *who = GetHitUnit())
                {
                    uint32 curSpellId = GetSpellInfo()->Id;
                    if (Aura* existingAura = who->GetAura(curSpellId))
                    {
                        playersAuraStacks[who->GetGUID()] = existingAura->GetStackAmount();
                    }
                }
            }

            void RemoveImmunity()
            {
                if (Unit* target = GetHitUnit())
                {
                    if (playersAuraStacks[target->GetGUID()])
                    {
                        if (Aura* existingAura = GetHitUnit()->GetAura(GetSpellInfo()->Id))
                        {
                            existingAura->SetStackAmount(playersAuraStacks[target->GetGUID()]+1);
                            existingAura->RefreshDuration();
                        }
                    }
                }
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_valithria_vigor_SpellScript::EnsureThatAurasStack);
                AfterHit += SpellHitFn(spell_valithria_vigor_SpellScript::RemoveImmunity);
            }
        private:
            std::map<uint64, uint8> playersAuraStacks;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_valithria_vigor_SpellScript();
        }
};

//End of Dream related NPCs and spells
class npc_column_of_frost_icc : public CreatureScript 
{
    public:
        npc_column_of_frost_icc() : CreatureScript("npc_column_of_frost_icc") { }

        struct npc_column_of_frost_iccAI : public ScriptedAI
        {
            npc_column_of_frost_iccAI(Creature* pCreature) : ScriptedAI(pCreature) { }
            void Reset()
            {
                events.ScheduleEvent(EVENT_CAST_COLUMN_OF_FROST, 2000);
                //Knockback value fix
                me->SetFloatValue(UNIT_FIELD_COMBATREACH, 50.0f);
            }
            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_COLUMN_OF_FROST:
                        {
                            uint32 effectId = RAID_MODE<uint32>(SPELL_COLUMN_EFFECT_10N, SPELL_COLUMN_EFFECT_10H_25N, SPELL_COLUMN_EFFECT_10H_25N, SPELL_COLUMN_EFFECT_25H);
                            DoCast(me, effectId, true);
                            events.ScheduleEvent(EVENT_DESPAWN, 3500);
                            break;
                        }
                        case EVENT_DESPAWN:
                            me->DespawnOrUnsummon();
                            break;
                        default:
                            break;
                    }
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_column_of_frost_iccAI(pCreature);
        }
};

class npc_icc_combat_stalker : public CreatureScript
{
    public:
        npc_icc_combat_stalker() : CreatureScript("npc_icc_combat_stalker") { }

        struct npc_icc_combat_stalkerAI : public ScriptedAI
        {
            npc_icc_combat_stalkerAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
            {
                pInstance = me->GetInstanceScript();
            }

            void DamageTaken(Unit* /*done_by*/, uint32& damage)
            {
                damage = 0;
                me->SetFullHealth();
            }
            void JustDied(Unit* killer)
            {
                if (Creature* valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER)))
                    DoScriptText(SAY_FAILURES, me);
            }
            void EnterCombat(Unit* who)
            {   
                bSummonColumns = false;
                bSummonZombies = true;
                bSummonAbominations = true;
                bSummonArchmages = true;
                bSummonSkeletons = true;
                bSummonSuppressors = true;

                events.Reset();
                events.ScheduleEvent(EVENT_CHECK_WIPE, 1000);
                if (Creature* valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER)))
                    AttackStart(valithria);
                me->getThreatManager().addThreat(who, 5000);
                DoZoneInCombat(me);
                m_uiSummonSkeletonTimer = 60000;
                m_uiSummonSuppressorTimer = 60000;
                events.ScheduleEvent(EVENT_SUMMON_ZOMBIE, 17000);
                events.ScheduleEvent(EVENT_SUMMON_ARCHMAGE, 2000);
                events.ScheduleEvent(EVENT_SUMMON_ABOMINATION, 10000);
                events.ScheduleEvent(EVENT_SUMMON_SUPPRESSOR, 20000);
                events.ScheduleEvent(EVENT_SUMMON_BLAZING_SKELETON, 5000);

                events.ScheduleEvent(EVENT_HASTEN_SUMMON_TIMER, 30000);
                events.ScheduleEvent(EVENT_CHECK_WIPE, 1000);
                pInstance->SetData(DATA_VALITHRIA_DREAMWALKER_EVENT, IN_PROGRESS);
                if (Creature* valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER)))
                    valithria->AI()->DoAction(EVENT_INTRO);

            }

            void MoveInLineOfSight(Unit *who)
            {
                if (!pInstance)
                    return;
                if (pInstance->GetData(DATA_VALITHRIA_DREAMWALKER_EVENT) == IN_PROGRESS)
                    return;
                if (me->IsWithinDistInMap(who, 80.0f, true) && who->GetTypeId() == TYPEID_PLAYER)
                    AttackStart(who);
                ScriptedAI::MoveInLineOfSight(who);
            }

            void EnterEvadeMode()
            {
                me->getThreatManager().clearReferences();
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
                summons.DespawnAll();
                events.Reset();
                ScriptedAI::EnterEvadeMode();
            }

            void JustSummoned(Creature* pSummoned)
            {
                if (Creature* valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER)))
                    pSummoned->AI()->AttackStart(valithria);
                summons.Summon(pSummoned);
            }

            void KilledUnit(Unit* /*victim*/)
            {
                if (Creature* valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER)))
                    DoScriptText(SAY_PDEATH, valithria);
            }

            void SummonCreature(uint32 entry, uint8 probability)
            {
                bool bSuccessfully = false;
                for (int i = 0; i < RAID_MODE(2,4,2,4); ++i)
                    if (urand(0, 100) < probability)
                    {
                        bSuccessfully = true;
                        DoSummon(entry, Pos[i]);
                    }
                //Nobody was summoned - summon at least one
                if (!bSuccessfully)
                    DoSummon(entry, Pos[urand(0, RAID_MODE(1,3,1,3))]);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!pInstance || pInstance->GetData(DATA_VALITHRIA_DREAMWALKER_EVENT) != IN_PROGRESS)
                    return;
                events.Update(diff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK_WIPE:
                        {
                            if (!SelectTarget(SELECT_TARGET_RANDOM, 0, 60.0f, true))
                            {
                                if (Creature* valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER)))
                                    valithria->AI()->DoAction(ACTION_WIPE);
                                Reset();
                                return;
                            }
                            else
                                events.ScheduleEvent(EVENT_CHECK_WIPE, 1000);
                            break;
                        }
                        case EVENT_SUMMON_ZOMBIE:
                        {
                            if (bSummonZombies)
                            {
                                SummonCreature(CREATURE_ZOMBIE, 50);
                            }
                            events.ScheduleEvent(EVENT_SUMMON_ZOMBIE, 30000);
                            break;
                        }
                        case EVENT_SUMMON_ARCHMAGE:
                        {
                            if (bSummonArchmages)
                                SummonCreature(CREATURE_ARCHMAGE, 75);
                            events.ScheduleEvent(EVENT_SUMMON_ARCHMAGE, 60000);
                            break;
                        }
                        case EVENT_SUMMON_ABOMINATION:
                        {
                            if (bSummonAbominations)
                                SummonCreature(CREATURE_ABOMINATION, 80);
                            events.ScheduleEvent(EVENT_SUMMON_ABOMINATION, 60000);
                            break;
                        }
                        case EVENT_SUMMON_SUPPRESSOR:
                        {
                            if (bSummonSuppressors)
                                SummonCreature(CREATURE_SUPPRESSOR, 60);
                            events.ScheduleEvent(EVENT_SUMMON_SUPPRESSOR, urand(m_uiSummonSuppressorTimer-2000, m_uiSummonSuppressorTimer+2000));
                            break;
                        }
                        case EVENT_SUMMON_BLAZING_SKELETON:
                        {
                            if (bSummonSkeletons)
                                SummonCreature(CREATURE_SKELETON, 80);
                            events.ScheduleEvent(EVENT_SUMMON_BLAZING_SKELETON, urand(m_uiSummonSkeletonTimer-2000, m_uiSummonSkeletonTimer+2000));
                            break;
                        }
                        case EVENT_HASTEN_SUMMON_TIMER:
                        {
                            //After 7/? (10/25 player) minutes, Suppressors and Blazing Skeletons start to spawn continuously
                            //(which usually leads to a quick wipe)
                            m_uiSummonSuppressorTimer -= 5000;
                            m_uiSummonSkeletonTimer -= 5000;
                            if (m_uiSummonSuppressorTimer < 2000)
                                m_uiSummonSuppressorTimer = 2000;
                            if (m_uiSummonSkeletonTimer < 2000)
                                m_uiSummonSkeletonTimer = 2000;
                            events.ScheduleEvent(EVENT_HASTEN_SUMMON_TIMER, 30000);
                            break;
                        }
                        default: 
                            break;
                    }
                }

            }
            private:
                InstanceScript* pInstance;

                uint32 m_uiSummonSkeletonTimer, m_uiSummonSuppressorTimer;
                SummonList summons;
                EventMap events;
                bool bSummonColumns, bSummonZombies, bSummonSuppressors, bSummonArchmages, bSummonSkeletons, bSummonAbominations;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_combat_stalkerAI(pCreature);
        }
};
class npc_icc_valithria_rot_worm : public CreatureScript
{
    public:
        npc_icc_valithria_rot_worm() : CreatureScript("npc_icc_valithria_rot_worm") { }

        struct npc_icc_valithria_rot_wormAI : public ScriptedAI
        {

            npc_icc_valithria_rot_wormAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
            }
            void Reset()
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CAST_ROT_WORM_SPAWN_ANIMATION, 500);
            }
            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_ROT_WORM_SPAWN_ANIMATION:  
                            DoCast(me, SPELL_SUMMON_ROT_WORM_VISUAL);
                            break;
                        default: 
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        private:
            EventMap events;
        };
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_valithria_rot_wormAI(pCreature);
        }
};

class npc_icc_valithria_gluttonous_abomination : public CreatureScript
{
    public:
        npc_icc_valithria_gluttonous_abomination() : CreatureScript("npc_icc_valithria_gluttonous_abomination") { }

        struct npc_icc_valithria_gluttonous_abominationAI : public ScriptedAI
        {

            npc_icc_valithria_gluttonous_abominationAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER));
            }
            void Reset()
            {
                bGutSprayReady = false;
                events.Reset();
            }
            void JustDied(Unit *pKiller)
            {
                Position pos;
                me->GetPosition(&pos);
                Creature *rotSummoner = DoSummon(CREATURE_TRIGGER, pos, 3000, TEMPSUMMON_TIMED_DESPAWN);
                rotSummoner->CastSpell(rotSummoner, SPELL_SUMMON_ROT_WORMS_AURA, true);
                rotSummoner->SetVisible(false);
                rotSummoner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                if (!me->isInCombat())
                    return;
                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DESPAWN:
                            me->DespawnOrUnsummon();
                            break;
                        case EVENT_GUT_SPRAY:
                            bGutSprayReady = true;
                            events.ScheduleEvent(EVENT_GUT_SPRAY, 5000);
                            break;
                        default:
                            break;
                    }
                }
                if (me->IsWithinMeleeRange(me->getVictim()))
                    if (bGutSprayReady)
                        bGutSprayReady = !DoSpellAttackIfReady(RAID_MODE<uint32>(SPELL_GUT_SPRAY_10N, SPELL_GUT_SPRAY_25N, SPELL_GUT_SPRAY_10H, SPELL_GUT_SPRAY_25H));
                DoMeleeAttackIfReady();
            }
        private:
            bool bGutSprayReady;
            EventMap events;  
            InstanceScript *pInstance;
            Creature *valithria;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_valithria_gluttonous_abominationAI(pCreature);
        }
};

class npc_icc_valithria_mana_void : public CreatureScript
{
    public:
        npc_icc_valithria_mana_void() : CreatureScript("npc_icc_valithria_mana_void") { }

        struct npc_icc_valithria_mana_voidAI : public ScriptedAI
        {

            npc_icc_valithria_mana_voidAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
            }
            void Reset()
            {
                events.ScheduleEvent(EVENT_DESPAWN, 30000);
            }
            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DESPAWN:
                            me->DespawnOrUnsummon();
                            break;
                    }
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_valithria_mana_voidAI(pCreature);
        }
};

class npc_icc_valithria_blistering_zombie : public CreatureScript
{
    public:
        npc_icc_valithria_blistering_zombie() : CreatureScript("npc_icc_valithria_blistering_zombie") { }

        struct npc_icc_valithria_blistering_zombieAI : public ScriptedAI
        {

            npc_icc_valithria_blistering_zombieAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER));
            }
            void Reset()
            {
                events.Reset();
            }
            void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
            {
                if (damageType != DIRECT_DAMAGE)
                    return;
                DoCast(target, RAID_MODE<uint32>(SPELL_CORROSION_10N, SPELL_CORROSION_25N, SPELL_CORROSION_10H, SPELL_CORROSION_25H));
            }
            void EnterCombat(Unit *who)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_EXPLODE, 25000);
            }
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                if (!me->isInCombat())
                    return;
                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_EXPLODE:
                            DoCast(me, RAID_MODE<uint32>(SPELL_ACID_BURST_10N, SPELL_ACID_BURST_25N, SPELL_ACID_BURST_10H, SPELL_ACID_BURST_25H));
                            events.ScheduleEvent(EVENT_EXPLODE, 25000);
                            break;
                        case EVENT_DESPAWN:
                            me->DespawnOrUnsummon();
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
            InstanceScript *pInstance;
            Creature *valithria;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_valithria_blistering_zombieAI(pCreature);
        }
};

class npc_icc_valithria_risen_archmage : public CreatureScript
{
    public:
        npc_icc_valithria_risen_archmage() : CreatureScript("npc_icc_valithria_risen_archmage") { }

        struct npc_icc_valithria_risen_archmageAI : public ScriptedAI
        {

            npc_icc_valithria_risen_archmageAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER));
            }
            void Reset()
            {
                events.Reset();
            }
            void EnterCombat(Unit *who)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CAST_COLUMN_OF_FROST, 4000);
                events.ScheduleEvent(EVENT_FROSTBOLT_VOLLEY, 8000);
                events.ScheduleEvent(EVENT_SUMMON_MANA_VOID, 14000);
            }
            void KilledUnit(Unit* victim)
            {
                DoStopAttack();
                DoResetThreat();
            }
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                if (!me->isInCombat())
                    return;
                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_COLUMN_OF_FROST:
                            if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(pTarget, SPELL_COLUMN_PRE);
                            events.ScheduleEvent(EVENT_CAST_COLUMN_OF_FROST, 10000);
                            break;
                        case EVENT_FROSTBOLT_VOLLEY:
                            DoCast(me, SPELL_FROSTBOLT_VOLLEY);
                            events.ScheduleEvent(EVENT_FROSTBOLT_VOLLEY, 5000);
                            break;
                        case EVENT_SUMMON_MANA_VOID:
                        {
                            if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(pTarget, SPELL_SUMMON_MANA_VOID);
                            events.ScheduleEvent(EVENT_SUMMON_MANA_VOID, 15000);
                            break;
                        }
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
            InstanceScript *pInstance;
            Creature *valithria;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_valithria_risen_archmageAI(pCreature);
        }
};

class npc_icc_valithria_supressor : public CreatureScript
{
    public:
        npc_icc_valithria_supressor() : CreatureScript("npc_icc_valithria_supressor") { }

        struct npc_icc_valithria_supressorAI : public ScriptedAI
        {
            npc_icc_valithria_supressorAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER));
            }
            void Reset()
            {
                events.Reset();
            }
            void EnterCombat(Unit *who)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CAST_SUPPRESSION, 8000);
            }
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                if (!me->isInCombat())
                    return;
                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_SUPPRESSION:
                            DoCast(valithria, SPELL_SUPPRESSION);
                            events.ScheduleEvent(EVENT_CAST_SUPPRESSION, 1000);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
            InstanceScript *pInstance;
            Creature *valithria;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_valithria_supressorAI(pCreature);
        }
};

class npc_icc_valithria_blazing_skeleton : public CreatureScript
{
    public:
        npc_icc_valithria_blazing_skeleton() : CreatureScript("npc_icc_valithria_blazing_skeleton") { }

        struct npc_icc_valithria_blazing_skeletonAI : public ScriptedAI
        {
            npc_icc_valithria_blazing_skeletonAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                valithria = Unit::GetCreature(*me, pInstance->GetData64(DATA_VALITHRIA_DREAMWALKER));
            }
            void Reset()
            {
                events.Reset();
            }
            void EnterCombat(Unit *who)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CAST_FIREBALL, 4000);
                events.ScheduleEvent(EVENT_CAST_LAY_WASTE, 8000);
            }
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                if (!me->isInCombat())
                    return;
                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_FIREBALL:
                            DoCast(me->getVictim(), SPELL_FIREBALL);
                            events.ScheduleEvent(EVENT_CAST_FIREBALL, 5000);
                            break;
                        case EVENT_CAST_LAY_WASTE:
                            DoCast(SPELL_LAY_WASTE);
                            events.ScheduleEvent(EVENT_CAST_LAY_WASTE, 20000);
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
            InstanceScript *pInstance;
            Creature *valithria;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_icc_valithria_blazing_skeletonAI(pCreature);
        }
};

void AddSC_boss_valithria()
{
    new boss_valithria();
    new npc_dreamportal_icc();
    new npc_dreamcloud_icc();
    new npc_icc_combat_stalker();
    new npc_valithria_alternative();
    new spell_valithria_summon_portal();
    new spell_valithria_vigor();
    new npc_column_of_frost_icc();
    new npc_icc_valithria_gluttonous_abomination();
    new npc_icc_valithria_mana_void();
    new npc_icc_valithria_rot_worm();
    new npc_icc_valithria_blistering_zombie();
    new npc_icc_valithria_supressor();
    new npc_icc_valithria_risen_archmage();
    new npc_icc_valithria_blazing_skeleton();
}