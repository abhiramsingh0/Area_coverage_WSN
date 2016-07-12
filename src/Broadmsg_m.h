//
// Generated file, do not edit! Created by opp_msgc 4.4 from Broadmsg.msg.
//

#ifndef _BROADMSG_M_H_
#define _BROADMSG_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0404
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>Broadmsg.msg</tt> by opp_msgc.
 * <pre>
 * message Broadmsg {
 *     int hopc;
 *     double xcor;
 *     double ycor;
 * }
 * </pre>
 */
class Broadmsg : public ::cMessage
{
  protected:
    int hopc_var;
    double xcor_var;
    double ycor_var;

  private:
    void copy(const Broadmsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Broadmsg&);

  public:
    Broadmsg(const char *name=NULL, int kind=0);
    Broadmsg(const Broadmsg& other);
    virtual ~Broadmsg();
    Broadmsg& operator=(const Broadmsg& other);
    virtual Broadmsg *dup() const {return new Broadmsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getHopc() const;
    virtual void setHopc(int hopc);
    virtual double getXcor() const;
    virtual void setXcor(double xcor);
    virtual double getYcor() const;
    virtual void setYcor(double ycor);
};

inline void doPacking(cCommBuffer *b, Broadmsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Broadmsg& obj) {obj.parsimUnpack(b);}


#endif // _BROADMSG_M_H_
