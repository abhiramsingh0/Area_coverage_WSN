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
#include "MadeSink.h"

Define_Module(MadeSink);

void MadeSink::initialize()
{
    nodes=100;
    int xnode,ynode,x=par(1),y=par(2);
    cPar& p = par(0);                                    // get address of 0th parameter from module.
    p.setLongValue(0);                                  //set parameter....value.
    cDisplayString& dispStr = getDisplayString();      // display on...
    dispStr.parse("p=$x,$y;r=10;r=17.3205080757");                          // ..network screen.
    //dispStr.parse("p=0,0");

    Broadmsg *msg = new Broadmsg("");
           msg->setHopc(0);
           msg->setXcor(0);
           msg->setYcor(0);
           // send(msg, "port$o");
           cModule *targetModule[nodes];

    for (int i=0; i<nodes; ++i){
        targetModule[i] = getParentModule()->getSubmodule("node",i);
        xnode=targetModule[i]->par(0);
        ynode=targetModule[i]->par(1);
        if(sqrt(pow((x-xnode),2)+pow((y-ynode),2))<= 17.3205080757){
            Broadmsg *copy = msg->dup();
            sendDirect(copy, targetModule[i], 0);
        }
    }

   // for (int i=0; i<nodes; i++)
    //    {
    //    Broadmsg *copy = msg->dup();
        //sendDirect(copy, "sport$o", i);
    //    sendDirect(copy, targetModule[i], 0);
     //   }
        delete msg;
}

void MadeSink::handleMessage(cMessage *msg){
    hm(check_and_cast<Broadmsg *>(msg));                            //type-casting is used.
       }

void MadeSink::hm(Broadmsg *msg){

              // int hopcount=msg->getHopc();                        //take out the values from the message.
              // hopcount=hopcount+1;
  //           ev << "hopcount: " << hopcount << "\n";          //print hop-count value contained in the message.
    //           msg->setHopc(0);                            // set the new values in the message.

      //         cPar& p = par(0);                                    // read 3rd parameter from module.
      //         p.setLongValue(0);                          //set parameter....value.
     //          cDisplayString& dispStr = getDisplayString();      // display on...
       //        dispStr.parse("t=$hcount");                          // ..network screen.
       //        send(msg, "sport$o",0);
}
