#HW8 Hashed Dictionary 

#Kenneth Chin

##Problem statement:
Implement a Hashed Dictionary. You will have to first implement the necessary functions in `HashedEntry.h`
(which inherits from `Entry.h`). The Dictionary must maintain an array of HashedEntries. 
Look at the implemented Constructor and toVector functions for insights. 
You have to add new HashedEntries to front of the list when the key has the same hash index.
Look at this link for insights on our implementation: https://en.wikipedia.org/wiki/Hash_table 

 
## Files to work in src
* `HashedEntry.h` Implement the necessary functions
* `HashedDictionary.h` Implement the necessary functions
* You can also modify `main.cpp` to debug your program.
      
## Exceptions to be thrown
* Throw the default exception in the function getItem() in `HashedDictionary.h` (when item is not found)

## Constraints 
* The class should support the following types via templates:
    * `<int,string>` (key is int, Item stored is string) 

## Notes
* Make sure your solution compiles and runs. **There are no points for code that doesn't compile**.
* The Initial code will **not necessarily** compile. You will have to write the necessary code.
* If you need to be considered for partial grade for any reason. Then email the staff before the deadline. Late email requests may not be considered.
* Post questions on Piazza if you have any questions.
* Please contact the course staff if you run into issues. We are here to help you!
