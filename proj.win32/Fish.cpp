#include "Fish.h"
#include "StaticData.h"

bool Fish::init(FishType type /* = k_Fish_Type_SmallFish */)
{
	_beCaught = false;
	_type = type;
	
	CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation_format"),_type);
	CCLog(animationName->getCString());
	CCAnimation* fishAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
	
	CCAnimate* fishAnimate = CCAnimate::create(fishAnimation);
	fishAnimate->setTag(k_Action_Animate);

	_fishSprite = CCSprite::create();	
	this->addChild(_fishSprite);
	_fishSprite->runAction(CCRepeatForever::create(fishAnimate));
	return true;
}

Fish* Fish::create(FishType type /*= k_Fish_Type_SmallFish */)
{
	Fish *fish = new Fish();
	fish->init(type);
	fish->autorelease();
	return fish;
}

int Fish::getScore()
{
	int score = 5*getFishType();
	return score;
}

int Fish::getSpeed()
{
	int speed = 200;
	return speed;
}


CCRect Fish::getCollisionArea(){//��ײ����
	CCSize size = _fishSprite->getContentSize();
	CCPoint point = _fishSprite->getParent()->convertToWorldSpace(_fishSprite->getPosition());

	return CCRectMake(point.x - size.width/2,
						point.y - size.height/4,// ���Գ�1/4Ч���ö����������� ԭ��ǰ������������ָ���½ǵ��Ǹ���
						size.width*0.8,size.height*0.5);
}

void Fish::beCaught(){
	if(!this->_beCaught){
		_beCaught = true;//����������ٱ�����
		stopActionByTag(k_Action_MoveTo);//��ֹͣ�ζ�
		stopActionByTag(k_Action_Animate);
		//this->stopAllActions();
		CCDelayTime *delayTime = CCDelayTime::create(1.0);
		CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(Fish::beCaught_CallFunc));
		CCSequence *seq = CCSequence::create(delayTime, callFunc, NULL);
		CCBlink *blink = CCBlink::create(1.0, 8);//����һ����˸�Ķ������� ����1��˸ʱ�䳤 ����2 ��˸����
		CCSpawn *spawn= CCSpawn::create(seq, blink, NULL);//�������ж��� ����  
		runAction(spawn);
	}
}

void Fish::beCaught_CallFunc(){
	if(isRunning()){
		_beCaught = false;//delaytime��Ļص�,�ָ����״̬
		this->stopActionByTag(k_Action_updatedirect);
		this->stopActionByTag(k_Action_MoveTo);
		this->stopActionByTag(k_Action_Animate);
		//this->stopAllActions();����ȫ��ֹͣ�Ļ��ͻ���ȫ����ʧ
		this->getParent()->removeChild(this,false);//false��bug��������ζ��ķ����ܰ��ձ��������ߡ����ƺ�seq2�йأ��޷�ֹͣ
												//����true�ֻᵼ���㱻������ٴβ�����ʱ������ʾ
		//CCLabelAtlas
		//this->stopAllActions();
	}
}

void Fish::moveTo(CCPoint destination){
	Fish_lastPoint = destination;
	CCPoint point = getParent()->convertToWorldSpace(this->getPosition());	
	float duration = ccpDistance(destination,point)/getSpeed();
	if(_type==13||_type==12||_type==10||_type==16 ){
		CCMoveTo *moveTo = CCMoveTo::create(duration,destination);
		CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(Fish::moveEnd));
		CCSequence *finite = CCSequence::create(moveTo,callFunc,NULL);
		finite->setTag(k_Action_MoveTo);
		this->runAction(finite);
		
	//float
		return ;
	}
	float _x = destination.x - point.x;
	float _y = destination.y - point.y;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize = this->getSize();//��ȡ��ǰ֡�Ĵ�С
	float min_start,min_destination,maxD;//��ȡ��С�ĳ�����ֱ����
	if(point.y > winSize.height *0.5){
		min_start = (winSize.height-fishSize.height*0.5) - point.y ;
	}else{
		min_start = point.y - fishSize.height*0.5;
	}
	if(destination.y > winSize.height *0.5){
		min_destination = (winSize.height-fishSize.height*0.5) - destination.y ;
	}else{
		min_destination = point.y - fishSize.height*0.5;
	}
	if(min_destination > min_start){
		maxD = min_start;
	}else{
		maxD = min_destination;
	}
	float rotation1,rotation2;//�������
	if(direction == 1){
		rotation1=1;
		if(point.y > winSize.height*0.5){
			rotation2=-1;
		}else{
			rotation2=1;
		}
	}else{
		rotation1=-1;
		if(point.y > winSize.height*0.5){
			rotation2=1;
		}else{
			rotation2=-1;
		}
	}
	// ���������������ߵ�cfg
	ccBezierConfig cfg;
	//_yΪ��ֱ ��ʼ�յ�߶Ȳ�
	cfg.controlPoint_1 = ccp(winSize.width*0.25*rotation1, (maxD+abs(_y))*rotation1*rotation2);
	cfg.controlPoint_2 = ccp(winSize.width*0.75*rotation1, -(maxD+abs(_y))*rotation1*rotation2);
	cfg.endPosition = ccp(_x,_y);
	CCLog("%f %f %f %f %f %f",cfg.controlPoint_1.x,cfg.controlPoint_1.y,cfg.controlPoint_2.x,cfg.controlPoint_2.y,cfg.endPosition.x,cfg.endPosition.y);
	float time = (ccpDistance(destination,point) + abs(_y))/getSpeed(); //����ʱ�� ������ٶ�  ������С������ϲ���׼ȷ����ʱ��
	// �����������ƶ�
	CCBezierBy* bezierForward = CCBezierBy::create(time, cfg);
	CCSequence* seq =  CCSequence::create(bezierForward, 
		CCCallFunc::create(this,callfunc_selector(Fish::moveEnd)),
		NULL);
	//����ͷ����
	CCDelayTime *delayTime = CCDelayTime::create(0.1);
	CCSequence* seq2 = CCSequence::create(delayTime, 
		CCCallFunc::create(this,callfunc_selector(Fish::updateActionDirection)),
		NULL);
	//CCSpawn *spawn = CCSpawn::create(seq,seq2,NULL);
	seq->setTag(k_Action_MoveTo);
	seq2->setTag(k_Action_updatedirect);
	this->runAction(seq);
	this->runAction(CCRepeatForever::create(seq2));//��ͷ�ζ�̫���� ԭ������ 1���������ʱ���moveend��ʱ��û��ֹͣaction 2���ı䷽���ʱ��ȥ��X��δ�ƶ���ֹͣ��
												   //3������������̫�����½Ƕȼ��㲨����С���ʣ�
												   //4�����ζ���ʱ��moveto��time�������ԡ�
												  //��bug�Ѿ��޸�
	//this->schedule(schedule_selector(Fish::updateDirection),1.0);
	
}
void Fish::moveEnd(){
	if(isRunning()){
			this->stopActionByTag(k_Action_updatedirect);
			this->stopActionByTag(k_Action_MoveTo);
			this->stopAllActions();
			this->stopActionByTag(k_Action_Animate);
			getParent()->removeChild(this,false);//
	}
}

//void Fish::reset(){
//	this->setRotation(0);
//	this->setVisible(true);
//}

CCSize Fish::getSize(){
	return _fishSprite->displayFrame()->getRect().size;//���д��ֻ�ܽ����������
}
void Fish::updateActionDirection()
{
	float point2X,point2Y;
	float point1X = Fish_lastPoint.x;//��һ���������
	float point1Y = Fish_lastPoint.y;

	point2X = this->getPositionX();//���ڵ�����
	point2Y = this->getPositionY();
	CCPoint start = CCPointMake(point2X, point2Y);
	// 	if(point2X==point1X){
	// 		return;
	// 	}
	if(this->_beCaught){//�������׽�Ͳ�������ķ����� ����˶�ֹͣ�ˣ���Ȼ�ϸ�������¸������X������ȵ�
		return;
	}
	if(abs(point1X-point2X)<20)//��ֹĳЩ����̫�������������»ε�̫����
		return;
	float angle = ccpAngleSigned(ccpSub(start,Fish_lastPoint),ccp(0,1));

	if(CC_RADIANS_TO_DEGREES(angle)<0 && direction == 0){
		setRotation(CC_RADIANS_TO_DEGREES(angle)+90);
		//CCLog("CC_RADIANS_TO_DEGREES = %f",CC_RADIANS_TO_DEGREES(angle));
	}
	else if(CC_RADIANS_TO_DEGREES(angle)>0 && direction == 1)
	{
		setRotation(CC_RADIANS_TO_DEGREES(angle)+90);
		//CCLog("CC_RADIANS_TO_DEGREES = %f",CC_RADIANS_TO_DEGREES(angle));
	}
	Fish_lastPoint = this->getPosition();//������һ������ȴ��¸��ص�����

}