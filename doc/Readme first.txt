
For UML diagrams :
 - Use the online tool : https://www.draw.io/
 - Save/Load UML diagram as XML local file and then push it on GIT in the "UML src" folder
 - Keep diagram as clean as possible (avoid crossing arrows or shapes hidden by another, and so on)
 	- If you need to focus on a particular point of the architecture, don't hesitate to create a dedicated diagram with all specifics details
 - Keep diagrams up to date
 - All diagram shall have as header a yellow note block that describe the purpose of the schema

Color scheme :
 - Black  : Core API classes
 - Green  : HMI control
 - Blue   : Abstrack classes or interfaces
 - Purple : Tiers API/Dependencies

 - Highlight in yellow class/properties/method that are not implemented but you want to put in the diagram (question? todo? ...)


UML class nomenclature :
 - "+" for public
 - "-" for private
 - "#" for friend
 - Prefix by "SLOT" or "SIGNAL" if needed


File naming convention :
 - CamelCase
 - No special char, no white space
 - <MainComponent>-<Topics>-<DiagramType>.xml

 - <MainCoponent> refer to a main component of the application, by example : TrackEngine, Core, GlobalDependencies, ...
 - <Topics> can be split in several topics and subtopics (separated by "-") : Overview, Drawing, Asynchronous, Cache, ...
 - <DiagramType> describe the type of the schema : Class, Sequence, DataFlow, SystemArchitecture, UseCase, ...