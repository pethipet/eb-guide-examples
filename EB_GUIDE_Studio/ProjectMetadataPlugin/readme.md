﻿# ProjectMetadataPlugin

Shows how to hook into the project life cycle of an EB GUIDE model.

## Instructions

### Prerequisite

* Visual Studio 2017 version 15.9 or later is installed
* EB GUIDE Studio is installed
* The source code of this extension example is locally available

### Setup

1. In Visual Studio, open the _EB\_GUIDE\_Studio\\EB\_GUIDE\_Studio\_examples.sln_ solution file.
2. Compile the _ProjectMetadataPlugin_ project.\
The _ProjectMetadataPlugin_ library file is created. 

### Run

1. Copy the _ProjectMetadataPlugin.dll_ into _$GUIDE\_INSTALL\_PATH\\studio\\lib\\core\\_.
2. Start EB GUIDE Studio.
3. Create a new project or load an existing project.\
A _metadata.json_ file is created and stored in the project folder.