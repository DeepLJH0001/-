#include "Counter.h"

 Counter::Counter(){
	 _digit = 0;
} 
 Counter::~Counter(){

 } 
 Counter * Counter::create(CCArray* presenters, int digit){
	 CCAssert(digit>=0 && digit<10,"�������ֻ����0��9֮��");
	 Counter *counter = new Counter;
	 if(counter && counter->init(presenters,digit))
	 {
			counter->autorelease();
			return counter;
	 }
	 else
	 {
		 CC_SAFE_DELETE(counter);
		 return NULL;
	 }
 }
 bool Counter::init(CCArray* presenters, int digit){
	 if(!CCNode::init()){
		return false;
	 }
	 _presenters = CCNode::create();
	 for(int i=0; i<10; i++){
		CCNode *node = (CCNode *)presenters->objectAtIndex(i);
		_presenters->addChild(node,0,i);//iΪ���õı�ǩ addChild(CCNode *child, int zOrder, int tag)
		CCSize size = node->getContentSize();
		node->setPosition(0.0f,i*size.height);
	 }
	 addChild(_presenters);
	 setDigit(digit);
	 return true;
 }
 void Counter::setDigit(int digit){
	 if(_digit != digit){
			_digit = digit;
		   animation(digit);
	 }
 }
 int Counter::getDigit(){
	 return _digit;
 }
 void Counter::animation(int digit){
	 _presenters->stopActionByTag(k_Counter_Action);
	 CCNode *node = (CCNode *)_presenters->getChildByTag(_digit);
	 CCPoint postion = node->getPosition();
	 CCMoveTo *moveTo = CCMoveTo::create(1.0f,ccp(0,-postion.y));//��ʦ3��̫��
	 moveTo->setTag(k_Counter_Action);
	 _presenters->runAction(moveTo);
 }
 void Counter::visit(){
	 glEnable(GL_SCISSOR_TEST);
	 CCPoint position = getPosition();
	 CCNode *presentor = _presenters->getChildByTag(_digit);
	 CCSize size = presentor->getContentSize();
	 CCPoint location = this->getParent()->convertToWorldSpace(
		 CCPointMake(position.x-size.width*0.5, 
					position.y-size.height*0.5));//���½ǵĵ�
	 glScissor(location.x*0.4,location.y*0.4,size.width*0.4,size.height*0.4);//�ü���Ӧ���ǹ����ľ��ο�Rect��x��y�ü���ԭ�㣬width��height�ü��Ŀ��
	 CCNode::visit();
	 glDisable(GL_SCISSOR_TEST);
 }