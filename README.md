# SamKnows

This library implements connectivity analytics. It is a work in progress and at the moment only http connection analytics are performed.

Some notes:
* My git usage was terrible, I am normally better at this but for some reason I just wrote most of the code, I guess maybe because I haven't used C in a while I was afraid of backstepping alot and I don't thing registering that in git would be usefull from a development point of view (it might be from an assessment pov so sorry).
* I don't think the assert usage is correct, I should find some other way of dealing with errors. I am used to having exceptions.
* I tried to think about an object oriented way of implementing stuff but quickly gave up
* The almost proxy like sk.h/c is a bit exaggerated but I think it does the job ob abstracting the implementation.
* Not having data structures or memory management was a problem, I was thinking of using glibc but I imagine that is not what you use.
* Not having namespaces like in C++ isn't great.
* I am using CMAKE and planning on getting a Makefile afterwards.
