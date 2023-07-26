set(ModulesFolder
    Modules)

# ############################### Building Modules #####################################################################

add_subdirectory(Modules/CommonMini)
add_subdirectory(Modules/RoadManager)

# ############################### Building Libraries ###################################################################

set_target_properties (RoadManager PROPERTIES FOLDER ${ModulesFolder} )
set_target_properties (CommonMini PROPERTIES FOLDER ${ModulesFolder} )

# ############################### Establish folder structure ###########################################################

set_folder(
    RoadManager
    ${ModulesFolder})
set_folder(
    CommonMini
    ${ModulesFolder})
