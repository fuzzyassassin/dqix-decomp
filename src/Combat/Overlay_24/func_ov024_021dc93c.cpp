#include <globaldefs.h>
#include "Combat/Overlay_0/GetCombatantByID.h"
#include "GameState/GameState.h"
extern "C" void* _Z17GetPtrField0x2a04P9GameState(GameState*);
extern "C" int _Z17ArrayContainsByteP23ArrayContainsByteStructi(void*,int);
extern "C" void _Z39IncrementByteCounterCapped0x63_0215a8d4Phi(void*,int);
extern "C" int _Z36CheckField0x14FiveFlagsClear020881c4Ph(void*);
extern "C" int _Z36CheckField0x14FiveFlagsClear0208810cPh(void*);
extern "C" void _Z26SetFlag0x800000AndByte0x24Pvh(void*,int);
extern "C" int _Z30SetFlag0x800000AndCall02088208Pvi(void*,void*);
extern "C" void _Z24ResetAndSetFlag0x1000000Pv(void*);
extern "C" int _Z27GetCodeForCategory_021e8c48Pvi(void*,signed char);
extern "C" unsigned short _Z31SelectByIndexRange0to3_021da644iii(int,int,int);
extern "C" void* func_ov000_0215e958(void*);
extern "C" void _Z33AddEntryAndIncrementCount0215a88cPvS_i(void*,void*,int);
extern "C" void _Z32AppendToChainAndIncCount0215ffc4PvS_i(void*,void*,int);
extern "C" void func_ov000_02159eac(void*,unsigned long long*,int);
extern "C" void func_ov000_0215cd44(void*,void*,GameObject*,short,unsigned long long,unsigned char);
extern "C" void func_ov000_0215af54(void*,int,int);
struct Action021dc93c {char pad[0x1c];unsigned char unused:7;unsigned char flag:1;};
struct Obj021dc93c {char pad[0xc];Action021dc93c* action;void* context;char pad14[0x71-0x14];unsigned char done;char pad72[2];unsigned char changed;};
struct Code021dc93c {unsigned int code:12;unsigned int rest:20;};
struct Triple021dc93c {unsigned int a:10;unsigned int b:10;unsigned int c:10;unsigned int rest:2;};
struct Params021dc93c {char pad[4];Code021dc93c field4;char pad8[0x1c];Triple021dc93c field24;char pad28[8];short count;};
struct Stats021dc93c {char pad[0x24];unsigned char stage;};
static inline void* GetCtx(Obj021dc93c* o){ SDK_NULL_ASSERT(o); return o->context; }
static inline int IsPartyIndex(int id){ return id>=0 && id<=3; }
// USA: func_ov024_021dc93c
extern "C" ARM void* func_ov024_021dc93c(Obj021dc93c* obj,short sourceID,int id,Params021dc93c* params,int amount,int unused,unsigned char enabled){
 GameObject* target=GetCombatantByID((int)obj->context,id);
 if(!target)return 0;
 int done=0;
 int ok=0;
 int message;
 unsigned long long effects=0;
 unsigned short code=params->field4.code;
 if(enabled){
  if(code==0x151 || code==0x152){
   if(code==0x151){
    if(_Z36CheckField0x14FiveFlagsClear020881c4Ph(target->currentStats_))ok=1;
   }else if(code==0x152){
    if(_Z36CheckField0x14FiveFlagsClear0208810cPh(target->currentStats_))ok=1;
   }
   int stage;
   int count=params->count;
   stage=((Stats021dc93c*)target->currentStats_)->stage;
   if(stage>=count)ok=0;
   if(ok){
    void* entry=func_ov000_0215e958(obj->context);
    if(!entry)return 0;
    func_ov000_0215cd44(obj->context,entry,target,stage,effects,obj->action->flag!=0);
    _Z32AppendToChainAndIncCount0215ffc4PvS_i(obj->action,entry,0);
    ++*((unsigned char*)obj->context+0x8e02);
    _Z33AddEntryAndIncrementCount0215a88cPvS_i(obj->context,entry,0x152);
    if(stage<count){
     message=0;
     while(stage<3){
      ++stage;
      switch(stage){case 1:message=0x31;break;case 2:message=0x32;break;case 3:message=0x33;break;}
      effects=0;
      func_ov000_02159eac(obj->context,&effects,0x23);
      void* step=func_ov000_0215e958(obj->context);
      if(!step)return 0;
      func_ov000_0215cd44(obj->context,step,target,stage,effects,obj->action->flag!=0);
      _Z32AppendToChainAndIncCount0215ffc4PvS_i(obj->action,step,0);
      ++*((unsigned char*)obj->context+0x8e02);
      obj->changed=1;
      _Z33AddEntryAndIncrementCount0215a88cPvS_i(obj->context,step,message);
     }
     if(count>=4){
      entry=func_ov000_0215e958(obj->context);
      if(!entry)return 0;
      _Z24ResetAndSetFlag0x1000000Pv(target->currentStats_);
      _Z33AddEntryAndIncrementCount0215a88cPvS_i(obj->context,entry,0x34);
      func_ov000_02159eac(obj->context,&effects,7);
      func_ov000_0215cd44(obj->context,entry,target,stage,effects,obj->action->flag!=0);
      _Z32AppendToChainAndIncCount0215ffc4PvS_i(obj->action,entry,0);
      ++*((unsigned char*)obj->context+0x8e02);
      obj->changed=1;
      _Z33AddEntryAndIncrementCount0215a88cPvS_i(obj->context,entry,message);
      func_ov000_0215af54(obj->context,id,0);
     }else{
      _Z26SetFlag0x800000AndByte0x24Pvh(target->currentStats_,count);
     }
    }
   }
  }else if(_Z36CheckField0x14FiveFlagsClear020881c4Ph(target->currentStats_)){
   int count=params->count;
   int total=((Stats021dc93c*)target->currentStats_)->stage+count;
   if(total>4)count-=total-4;
   for(;count>0;count--){
    int result=_Z30SetFlag0x800000AndCall02088208Pvi(target->currentStats_,GetCtx(obj));
    effects=0;
    message=_Z27GetCodeForCategory_021e8c48Pvi(obj,result);
    void* entry=func_ov000_0215e958(obj->context);
    if(!entry)return 0;
    if(result>0){
     func_ov000_02159eac(obj->context,&effects,0x23);
     if(result==4){
      func_ov000_02159eac(obj->context,&effects,7);
      func_ov000_0215af54(obj->context,id,0);
      void* list=_Z17GetPtrField0x2a04P9GameState(GameState::GetInstance());
      if(_Z17ArrayContainsByteP23ArrayContainsByteStructi(list,sourceID) && code==0xa8)
       _Z39IncrementByteCounterCapped0x63_0215a8d4Phi(obj->context,3);
     }
    }else{
     effects=0;
     result=0;
    }
    func_ov000_0215cd44(obj->context,entry,target,result,effects,obj->action->flag!=0);
    _Z32AppendToChainAndIncCount0215ffc4PvS_i(obj->action,entry,0);
    ++*((unsigned char*)obj->context+0x8e02);
    obj->changed=1;
    _Z33AddEntryAndIncrementCount0215a88cPvS_i(obj->context,entry,message);
   }
   done=1;
  }else{
   void* entry=func_ov000_0215e958(obj->context);
   if(!entry)return 0;
   func_ov000_0215cd44(obj->context,entry,target,0,0,obj->action->flag!=0);
   _Z32AppendToChainAndIncCount0215ffc4PvS_i(obj->action,entry,0);
   ++*((unsigned char*)obj->context+0x8e02);
   obj->changed=1;
   _Z33AddEntryAndIncrementCount0215a88cPvS_i(obj->context,entry,_Z31SelectByIndexRange0to3_021da644iii(id,params->field24.b,params->field24.c));
  }
 }
 if(IsPartyIndex(id) && done)obj->done=1;
 return 0;
}
