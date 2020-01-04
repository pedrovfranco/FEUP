mtype = { msg0, msg1, ack0, ack1 };
chan sender = [1] of { mtype };
chan receiver = [1] of { mtype };


active proctype Sender()
{
do
::
if
:: receiver?msg0;
:: skip
fi;
do
:: sender?ack0 -> break
:: sender?ack1
:: timeout ->
if
::
send0: receiver!msg0;
:: skip
fi;
od;
::
if
:: receiver?msg1;
:: skip
fi;
do
:: sender?ack1 -> break
:: sender?ack0
:: timeout ->
if
::
send1: receiver!msg1;
:: skip
fi;
od;
FEUP-DEI Page 1 of 5
od;
}


active proctype Receiver()
{
do
::
do
:: receiver?msg0 ->
sender!ack0; break;
:: receiver?msg1 ->
sender!ack1
od
do
:: receiver?msg1 ->
sender!ack1; break;
:: receiver?msg0 ->
sender!ack0
od
od
}
