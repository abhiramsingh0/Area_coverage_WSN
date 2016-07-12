//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
#include <omnetpp.h>
#include "Broadmsg_m.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

class Node: public cSimpleModule
{
protected:
    double myx;
    double myy;
    int nodes;
    char state;
    int firstmsg;
    double parentx, parenty;
    double crange;
    cMessage *timeoutmsg;
    simtime_t ptimer;
    double neighbors[150][2];
    double ipoints[150][2];
    int leftneighbor,rightneighbor;
    int activenodes;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void hm(Broadmsg *msg);
    double finddistance(double xpos,double ypos);
    double findangle(double xpos,double ypos);
    double timer1(double distance,double angle);
    void makeentry(double xpos,double ypos);
    int circle_circle_intersection(double x0, double ypos0, double r0,
                                       double x1, double ypos1, double r1,
                                       double *xi, double *yi,
                                       double *xi_prime, double *yi_prime);
    double timer2(double distance,double distance1);
    int checkcoverage();
    double findslope(double xpos,double ypos);
    double findintercept(double slope);
};
Define_Module(Node);

void Node::initialize(){
    nodes=1000;
    myx=(double)par(0);
    myy=(double)par(1);
    state='w';
    firstmsg=0;
    crange=17.3205080757;
    ptimer=0;
    leftneighbor=rightneighbor=0;
    activenodes=0;
    cDisplayString& dispStr = getDisplayString();
    dispStr.parse("p=$x,$y;i=misc/node_vs");                                        //use module parameters at run time.
    ev<<"node vector"<<getIndex()<<"xpos\t"<< myx<< "ypos"<< myy<<"\n";
    for(int i=0;i<150;i++){
        for(int j=0;j<2;j++){
            ipoints[i][j]=999.0;
            neighbors[i][j]=999.0;
        }
    }
//    neighbors[0][0]=myx;
//    neighbors[0][1]=myy;
}

void Node::handleMessage(cMessage *msg){
    if(state=='w'){
        if (msg->isSelfMessage()==1) {                                                              // timeout expired.
            delete msg;
            state='a';
            cDisplayString& dispStr = getDisplayString();
            dispStr.parse("i=misc/square_vl;r=10");
            Broadmsg *msg = new Broadmsg("");
            msg->setHopc((int)par(2));                                                         // set the new values in the message.
            msg->setXcor(myx);
            msg->setYcor(myy);
            cModule *targetModule;
            for (int i=0; i<nodes; ++i){
                if(getIndex()==i){                                                      //check if i is the index of transmitting node.
                    continue;
                }
                targetModule = getParentModule()->getSubmodule("node",i);
                double xnode=targetModule->par(0);
                double ynode=targetModule->par(1);
                if(finddistance(xnode,ynode)<= crange){
                    Broadmsg *copy = msg->dup();
                    sendDirect(copy, targetModule, 0);
                }
            }
            delete msg;
            cModule *parentmodule=getParentModule();
            parentmodule->par(0)=(int)parentmodule->par(0)+1;
            ev << "active nodes" << (int)parentmodule->par(0) <<"\n";
        }
        else{
        hm(check_and_cast<Broadmsg *>(msg));                            //type-casing is used.
        }
    }
    else{
        delete msg;
    }
}

void Node::hm(Broadmsg *msg){
    double xpos=msg->getXcor();                                    //take out the values from the message.
    double ypos=msg->getYcor();
    int hopcount=msg->getHopc();
    delete msg;
    simtime_t timeout;
    double distance=finddistance(xpos,ypos);
    double angle=findangle(xpos,ypos);
    makeentry(xpos, ypos);
    if (++firstmsg==1){
        cPar& p = par(2);                                  // read 3rd parameter from module.
        p.setLongValue(hopcount+1);                        //set parameter....value.
        parentx=xpos;
        parenty=ypos;
        timeout=timer1(distance, angle);        
        timeoutmsg = new cMessage("timeoutmsg");
        scheduleAt(simTime()+timeout, timeoutmsg);
        ptimer=simTime()+timeout;
        ev<<"timervalue\t"<<ptimer<<" module\t"<<getIndex();
    }
    else{
        double distance1=finddistance(parentx,parenty);
        if(((int)par("hcount")>hopcount)&&(distance1>distance)){				// msg from lower level.
            if(ptimer>=simTime())
                cancelEvent(timeoutmsg);
            parentx=xpos;
            parenty=ypos;
            timeout=timer1(distance,angle);	    
            scheduleAt(simTime()+timeout, timeoutmsg);
            ptimer=simTime()+timeout;
        }                                                                                   //end of if, for msg received from lower level
        else if((int)par("hcount")==hopcount){                                              // msg is received from same level
            double m=findslope(parentx,parenty);
            double c=findintercept(m);
            double pfrmline=ypos-m*xpos-c;
            if (leftneighbor==0 && rightneighbor==0){
                if (ptimer>=simTime())
                    cancelEvent(timeoutmsg);
                timeout=timer2(distance,distance1);
                scheduleAt(simTime()+timeout, timeoutmsg);
                ptimer=simTime()+timeout;
                ev<<"timervalue\t"<<ptimer<<" module\t"<<getIndex();
                if(pfrmline<0){
                    leftneighbor=1;
                }
                else{
                    rightneighbor=1;
                }
            }
/*            else if(leftneighbor==0 && rightneighbor==1 && pfrmline<0){
                if(pfrmline<0){
                    leftneighbor=1;
                    checkcoverage();
                }
            }
            else if(leftneighbor==1 && rightneighbor==0 && pfrmline>=0){
                rightneighbor=1;
                checkcoverage();
            }*/
            else{
                if(ptimer>=simTime())
                    cancelEvent(timeoutmsg);
                timeout=timer1(distance,angle);
                scheduleAt(simTime()+timeout, timeoutmsg);
                ptimer=simTime()+timeout;
                checkcoverage();
            }
        }                                                                                   //end of else if((int)par("hcount")==hopcount)
        else{                                                                               // msg from higher level
            if(ptimer>=simTime())
                cancelEvent(timeoutmsg);
            timeout=timer1(distance,angle);
            scheduleAt(simTime()+timeout, timeoutmsg);
            ptimer=simTime()+timeout;
            checkcoverage();
        }
    }                                                                                       //else corresponding to if(++firstmsg==1).
}                                                                                           //end of function hm()

double Node::finddistance(double xpos,double ypos){
    return (sqrt(pow((myx-xpos),2)+pow((myy-ypos),2)));
}

double Node::findangle(double xpos,double ypos){
    double x=xpos-myx;
    double y=ypos-myy;
    if(x>0 && y>0){                                                     //1st quadrant
        return ((atan(y/x)*180)/M_PI);
    }
    else if(x<0 && y>0){                                                //2nd quadrant
        return (180.0+((atan(y/x)*180)/M_PI));
    }
    else if(x<0 && y<0){                                                //3rd quadrant
        return (180.0+((atan(y/x)*180)/M_PI));
    }
    else{                                                               //4th quadrant
        return (360.0+((atan(y/x)*180)/M_PI));
    }
}

double Node::timer1(double distance,double angle){
    if((crange-distance)>=0)
        return (((crange-distance)*100)+(angle/10));
    else
        return (((distance-crange)*100)+(angle/10));
}

void Node::makeentry(double xpos,double ypos){
    int i;
    double x3, y3, x3_prime, y3_prime;
    int w;
    for(i=0;neighbors[i][0]!=999.0;i++);
    neighbors[i][0]=xpos;
    neighbors[i][1]=ypos;
    int j;
    for(j=0;j<i;j++){
        w=circle_circle_intersection(neighbors[j][0],neighbors[j][1], crange, xpos, ypos, crange, &x3, &y3, &x3_prime, &y3_prime);
        if(w==0)continue;
        if(finddistance(x3,y3)<=crange){
            for(i=0;ipoints[i][0]!=999.0;i++);
            ipoints[i][0]=x3;
            ipoints[i][1]=y3;
        }
        if(finddistance(x3_prime,y3_prime)<=crange){
                    for(i=0;ipoints[i][0]!=999.0;i++);
                    ipoints[i][0]=x3_prime;
                    ipoints[i][1]=y3_prime;
        }
    }
}

int Node::circle_circle_intersection(double x0, double ypos0, double r0,
                               double x1, double ypos1, double r1,
                               double *xi, double *yi,
                               double *xi_prime, double *yi_prime)
{
  double a, dx, dy, d, h, rx, ry;
  double x2, y2;
  /* dx and dy are the vertical and horizontal distances between
   * the circle centers.
   */
  dx = x1 - x0;
  dy = ypos1 - ypos0;

  /* Determine the straight-line distance between the centers. */
  //d = sqrt((dy*dy) + (dx*dx));
  d = hypot(dx,dy); // Suggested by Keith Briggs

  /* Check for solvability. */
  if (d > (r0 + r1))
  {
    /* no solution. circles do not intersect. */
  *xi = 999.0;
  *xi_prime =999.0;
  *yi = 999.0;
  *yi_prime = 999.0;
    return 0;
  }
  if (d < fabs(r0 - r1))
  {
    /* no solution. one circle is contained in the other */
  *xi = 999.0;
  *xi_prime =999.0;
  *yi = 999.0;
  *yi_prime =999.0;
    return 0;
  }

  /* 'point 2' is the point where the line through the circle
   * intersection points crosses the line between the circle
   * centers.
   */

  /* Determine the distance from point 0 to point 2. */
  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

  /* Determine the coordinates of point 2. */
  x2 = x0 + (dx * a/d);
  y2 = ypos0 + (dy * a/d);

  /* Determine the distance from point 2 to either of the
   * intersection points.
   */
  h = sqrt((r0*r0) - (a*a));

  /* Now determine the offsets of the intersection points from
   * point 2.
   */
  rx = -dy * (h/d);
  ry = dx * (h/d);

  /* Determine the absolute intersection points. */
  *xi = x2 + rx;
  *xi_prime = x2 - rx;
  *yi = y2 + ry;
  *yi_prime = y2 - ry;
  return 1;
}

double Node::timer2(double distance,double distance1){
    return (distance1>distance?(1/(pow(distance,2)+pow(distance1,2))):(1/(pow(distance,2)+pow(distance1,2))+uniform(0,1)));
}

int Node::checkcoverage(){
    int i,j;
    for(i=1;neighbors[i][0]!=999.0;i++){
        for(j=0;j<150;j++){
            if(ipoints[j][0]==999.0){
                continue;
            }
            if(sqrt(pow((neighbors[i][0]-ipoints[j][0]),2)+pow((neighbors[i][1]-ipoints[j][1]),2))<crange){
                ipoints[j][0]=999.0;
                ipoints[j][1]=999.0;
            }
        }
    }
    for(j=0;j<150;j++){
        if(ipoints[j][0]!=999.0) return 0;                          // not fully covered then return 0
    }
    state='s';
    return 1;                                                       // fully covered
}

double Node::findslope(double xpos,double ypos){
    double x=xpos-myx;
    double y=ypos-myy;
    return tan(y/x);
}

double Node::findintercept(double slope){
    return (myy-slope*myx);
}




/*           ev << "hopcount: " << hopcount << "\n";            //print hop-count value contained in the message.

               if(distance<= crange){
                   cPar& p = par(2);                                    // read 3rd parameter from module.
                   p.setLongValue(hopcount);                          //set parameter....value.
                   cDisplayString& dispStr = getDisplayString();      // display on...
                   dispStr.parse("t=$hcount");
               }
            //   timeout=crange-sqrt(pow((myx-xpos),2)+pow((myy-ypos),2));

             //  cPar& p = par(2);                                    // read 3rd parameter from module.
              // p.setLongValue(hopcount);                          //set parameter....value.
              // cDisplayString& dispStr = getDisplayString();      // display on...
              // dispStr.parse("t=$hcount");                          // ..network screen.
       //        send(msg, "port$o",1);                                                                                            */
