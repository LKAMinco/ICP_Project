ICP PROJECT 2022
Class and sequence diagram editor

Authors:
Jakub Julius Smykal (xsmyka01)
Milan Hrabovsky (xhrabo15)

Design patterns:
Observer - updates data in sequence diagram based on changes
           in class diagram
Adapter - class diagram scene passes along method calls to class storage

Installation & use:
- build code using command 'make'
- use 'make run' to start the application
- use 'make doxygen' to generate documentation
- use 'make clean' to remove build files

! Qt & doxygen required for all commands to work !

User Experience:
UX is implemented through ui elements like buttons and context menu. Diagrams
contain interactable entities and connection line, which can by selected and modified
through user interface or keyboard input. Keyboard input is restricted to renaming
classes, methods and attributes.

Interconnection between diagrams:
Changes in class diagram will be instantly reflected in sequence diagrams.
These changes include creating/removing class or method & renaming class or method.
Inconsistency is solved by using ComboBox element to prevent user from inserting invalid
methods in sequence diagrams.

Save files:
- .json format
- example in 'examples' directory

Missing functionality:
- undo & redo not implemented
- missing warning when deleting class entity, that is being used in sequence diagram
- missing 'save as' context window when opening/creating new file
- size of lifeline in sequence diagram cannot be changed