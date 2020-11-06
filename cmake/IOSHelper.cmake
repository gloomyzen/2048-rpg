function(_set_attr_to_all_target attr_name attr_value type)
    if (${type} STREQUAL "project")
        set_xcode_property(${APP_NAME} ${attr_name} ${attr_value})
    else ()
        set_xcode_property(cocos2d ${attr_name} ${attr_value})
        set_xcode_property(dragonbones_target ${attr_name} ${attr_value})
        set_xcode_property(ext_clipper ${attr_name} ${attr_value})
        set_xcode_property(ext_convertUTF ${attr_name} ${attr_value})
        set_xcode_property(ext_edtaa3func ${attr_name} ${attr_value})
        set_xcode_property(ext_md5 ${attr_name} ${attr_value})
        set_xcode_property(ext_poly2tri ${attr_name} ${attr_value})
        set_xcode_property(ext_recast ${attr_name} ${attr_value})
        set_xcode_property(ext_tinyxml2 ${attr_name} ${attr_value})
        set_xcode_property(ext_unzip ${attr_name} ${attr_value})
        set_xcode_property(ext_xxhash ${attr_name} ${attr_value})
        set_xcode_property(ext_xxtea ${attr_name} ${attr_value})
        set_xcode_property(external ${attr_name} ${attr_value})
        set_xcode_property(project_dependency ${attr_name} ${attr_value})
        set_xcode_property(project_warning ${attr_name} ${attr_value})
    endif ()
endfunction()

function(set_attr_to_all_target attr_name attr_value type)
    if (${type} STREQUAL "all")
        _set_attr_to_all_target(${attr_name} ${attr_value} "project")
        _set_attr_to_all_target(${attr_name} ${attr_value} "not_project")
    elseif (${type} STREQUAL "not_project")
        _set_attr_to_all_target(${attr_name} ${attr_value} "not_project")
    else ()
        _set_attr_to_all_target(${attr_name} ${attr_value} "project")
    endif ()
endfunction()