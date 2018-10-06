# SamKnows

This library implements connectivity analytics. It is a work in progress and at the moment only http connection analytics are performed.

Notes:
* Didn't know what to do if http return codes changed so I decided to calculate median every time and print that. Sorry for breaking the rules.
* I don't think the assert usage is correct, I should find some other way of dealing with errors. I am used to having exceptions.
