# RoadManager (esmini)

Forked from [esmini](https://github.com/esmini/esmini/)

## Why dynamic linking?

Because static + singleton (`roadmanager::OpenDrive`) + many DLLs on UE side interacting with RoadManager = problems. Each DLL ends up having its own singleton instance, i.e. its own OpenDrive.
