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


CCRect Fish::getCollisionArea(){//碰撞地区
	CCSize size = _fishSprite->getContentSize();
	CCPoint point = _fishSprite->getParent()->convertToWorldSpace(_fishSprite->getPosition());

	return CCRectMake(point.x - size.width/2,
						point.y - size.height/4,// 调试成1/4效果好多了撒网上移 原本前面俩个参数是指左下角的那个点
						size.width*0.8,size.height*0.5);
}

void Fish::beCaught(){
	if(!this->_beCaught){
		_beCaught = true;//被捕获后不能再被捕获
		stopActionByTag(k_Action_MoveTo);//鱼停止游动
		stopActionByTag(k_Action_Animate);
		//this->stopAllActions();
		CCDelayTime *delayTime = CCDelayTime::create(1.0);
		CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(Fish::beCaught_CallFunc));
		CCSequence *seq = CCSequence::create(delayTime, callFunc, NULL);
		CCBlink *blink = CCBlink::create(1.0, 8);//创建一个闪烁的动作对象 参数1闪烁时间长 参数2 闪烁次数
		CCSpawn *spawn= CCSpawn::create(seq, blink, NULL);//产生并行动作 并发  
		runAction(spawn);
	}
}

void Fish::beCaught_CallFunc(){
	if(isRunning()){
		_beCaught = false;//delaytime后的回调,恢复鱼的状态
		this->stopActionByTag(k_Action_updatedirect);
		this->stopActionByTag(k_Action_MoveTo);
		this->stopActionByTag(k_Action_Animate);
		//this->stopAllActions();这里全部停止的话就会鱼全部消失
		this->getParent()->removeChild(this,false);//false有bug导致鱼的游动的方向不能按照贝塞尔曲线。估计和seq2有关，无法停止
												//设置true又会导致鱼被捕获后再次产生的时候不能显示
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
	CCSize fishSize = this->getSize();//获取当前帧的大小
	float min_start,min_destination,maxD;//获取最小的场景垂直距离
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
	float rotation1,rotation2;//方向控制
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
	// 贝塞尔的左右切线点cfg
	ccBezierConfig cfg;
	//_y为垂直 开始终点高度差
	cfg.controlPoint_1 = ccp(winSize.width*0.25*rotation1, (maxD+abs(_y))*rotation1*rotation2);
	cfg.controlPoint_2 = ccp(winSize.width*0.75*rotation1, -(maxD+abs(_y))*rotation1*rotation2);
	cfg.endPosition = ccp(_x,_y);
	CCLog("%f %f %f %f %f %f",cfg.controlPoint_1.x,cfg.controlPoint_1.y,cfg.controlPoint_2.x,cfg.controlPoint_2.y,cfg.endPosition.x,cfg.endPosition.y);
	float time = (ccpDistance(destination,point) + abs(_y))/getSpeed(); //持续时间 距离除速度  距离最小二乘拟合才能准确计算时间
	// 贝塞尔曲线移动
	CCBezierBy* bezierForward = CCBezierBy::create(time, cfg);
	CCSequence* seq =  CCSequence::create(bezierForward, 
		CCCallFunc::create(this,callfunc_selector(Fish::moveEnd)),
		NULL);
	//调整头朝向
	CCDelayTime *delayTime = CCDelayTime::create(0.1);
	CCSequence* seq2 = CCSequence::create(delayTime, 
		CCCallFunc::create(this,callfunc_selector(Fish::updateActionDirection)),
		NULL);
	//CCSpawn *spawn = CCSpawn::create(seq,seq2,NULL);
	seq->setTag(k_Action_MoveTo);
	seq2->setTag(k_Action_updatedirect);
	this->runAction(seq);
	this->runAction(CCRepeatForever::create(seq2));//鱼头晃动太厉害 原因大概是 1，被捕获的时候和moveend的时候没有停止action 2，改变方向的时候去除X轴未移动（停止）
												   //3，贝塞尔曲线太陡导致角度计算波动（小概率）
												   //4，鱼游动的时候moveto的time参数不对。
												  //该bug已经修复
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
	return _fishSprite->displayFrame()->getRect().size;//这个写法只能解决部分问题
}
void Fish::updateActionDirection()
{
	float point2X,point2Y;
	float point1X = Fish_lastPoint.x;//上一个点的坐标
	float point1Y = Fish_lastPoint.y;

	point2X = this->getPositionX();//现在的坐标
	point2Y = this->getPositionY();
	CCPoint start = CCPointMake(point2X, point2Y);
	// 	if(point2X==point1X){
	// 		return;
	// 	}
	if(this->_beCaught){//如果被捕捉就不用做鱼的方向处理 鱼的运动停止了，显然上个坐标和下个坐标的X都是相等的
		return;
	}
	if(abs(point1X-point2X)<20)//防止某些曲线太陡计算误差而导致晃的太厉害
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
	Fish_lastPoint = this->getPosition();//保存上一个坐标等待下个回调进来

}