# define relative path filename from __FILE__
function(redefine_file_macro targetname microname)
    # get target source files.
    get_target_property(source_files "${targetname}" SOURCES)
    # loop source files.
    foreach (sourcefile ${source_files})
        # get compile defines.
        get_property(defs SOURCE "${sourcefile}"
                PROPERTY COMPILE_DEFINITIONS)
        # get file absolute path
        get_filename_component(filepath "${sourcefile}" ABSOLUTE)
        # get relative path
        string(REPLACE ${PROJECT_SOURCE_DIR}/ "" relpath ${filepath})
        # define micro
        list(APPEND defs "${microname}=\"${relpath}\"")
        # redefine compile defines.
        set_property(
                SOURCE "${sourcefile}"
                PROPERTY COMPILE_DEFINITIONS ${defs}
        )
    endforeach ()
endfunction()