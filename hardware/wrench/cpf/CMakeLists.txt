IF ( BUILD_TESTS)
IF ( BUILD_WRENCH_TEST )

    INSTALL_FILES( /cpf [^.]*.cpf)  
    INSTALL_FILES( /cpf [^.]*.dtd)  

ENDIF ( BUILD_WRENCH_TEST )
ENDIF ( BUILD_TESTS )