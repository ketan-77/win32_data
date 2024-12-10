void tfcmConfReader::getCurrProtPhsOvrCurrentConfig(void)
{

    uint32_t noOfRows = 0;
    eApp_t_TableIndex tableIndex = 0;
    int i = 0;
    addSettingNodeBlock("Gn 50 Measurement", confData[0].curProtPhsOvrCurr., std::to_string(1), std::to_string(1), std::to_string(1));
    addSettingNodeBlock("Gn 51 Measurement", confData[0].curProtPhsOvrCurr., std::to_string(1), std::to_string(1), std::to_string(1));

    parRc = ::eAppParameterGetScalarInt8ValueInst(eAppPar_DbInst_App, "currProc_phOvercurr_gnChAngl", &confData[0].curProtPhsOvrCurr.gnChAngl);
    if (parRc != eAppPar_GetResult_OK)
    {
        EAPP_LOG_FAT("Falied to read currProc_phOvercurr_gnChAngl : %d", parRc);
    }

    parRc = ::eAppParameterGetScalarFloat32ValueInst(eAppPar_DbInst_App, "currProc_phOvercurr_gn67MinVtg", &confData[0].curProtPhsOvrCurr.gn67MinVtg);
    if (parRc != eAppPar_GetResult_OK)
    {
        EAPP_LOG_FAT("Falied to read currProc_phOvercurr_gn67MinVtg : %d", parRc);
    }
    addSettingNodeBlock("Gn 67 Char Angle", realTostr(confData[0].curProtPhsOvrCurr.gn67MinVtg, 2), std::to_string(0), std::to_string(1), std::to_string(-1));

    parRc = ::eAppParameterGetScalarStringValueInst(eAppPar_DbInst_App, "currProc_phOvercurr_gn672outof3Logic", strData, sizeof(strData));
    if (parRc != eAppPar_GetResult_OK)
    {
        EAPP_LOG_FAT("Falied to read currProc_phOvercurr_gn672outof3Logic : %d", parRc);
    }
    if (strData[0] == emptyChar)
    {
        EAPP_LOG_FAT("Param currProc_phOvercurr_gn672outof3Logic is empty");
    }
    confData[0].curProtPhsOvrCurr.gn672outof3Logic = strData;
    addSettingNodeBlock("Gn 67 2-out-of-3 Logic", confData[0].curProtPhsOvrCurr.gn672outof3Logic, std::to_string(0), std::to_string(1), std::to_string(1));

    parRc = ::eAppParameterGetScalarStringValueInst(eAppPar_DbInst_App, "currProc_phOvercurr_gn50Measure", strData, sizeof(strData));
    if (parRc != eAppPar_GetResult_OK)
    {
        EAPP_LOG_FAT("Falied to read currProc_phOvercurr_gn50Measure : %d", parRc);
    }
    if (strData[0] == emptyChar)
    {
        EAPP_LOG_FAT("Param currProc_phOvercurr_gn50Measure is empty");
    }
    confData[0].curProtPhsOvrCurr.gn50Measure = strData;
    addSettingNodeBlock("Gn 67 Minimum Voltage", confData[0].curProtPhsOvrCurr.gn50Measure, std::to_string(1), std::to_string(1), std::to_string(1));

    parRc = ::eAppParameterGetScalarStringValueInst(eAppPar_DbInst_App, "currProc_phOvercurr_gn51Measure", strData, sizeof(strData));
    if (parRc != eAppPar_GetResult_OK)
    {
        EAPP_LOG_FAT("Falied to read currProc_phOvercurr_gn51Measure : %d", parRc);
    }
    if (strData[0] == emptyChar)
    {
        EAPP_LOG_FAT("Param currProc_phOvercurr_gn51Measure is empty");
    }
    confData[0].curProtPhsOvrCurr.gn51Measure = strData;

    strData[0] = emptyChar;

    //Table - 51_Table

    parRc = ::eAppParameterDiscoverRecordNumInst(eAppPar_DbInst_App, "51_Table", &noOfRows);
    if (parRc != eAppPar_GetResult_OK)
    {
        EAPP_LOG_FAT("get table '51_Table', reading table rows failed : %d ", parRc);
    }
    parRc = ::eAppParameterDiscoverNextTableIndex("51_Table", tableIndex, &tableIndex);
    while (parRc == eAppPar_GetResult_OK)
    {
        parRc = ::eAppParameterGetTableStringValue("51_Table", "GroupName", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column GroupName : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param GroupName is empty");
        }
        confData[0].curProtPhsOvrCurr.phc51_table[i].GroupName = strData;

        parRc = ::eAppParameterGetTableStringValue("51_Table", "511Elmnt", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511Elmnt : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 511Elmnt is empty");
        }
        confData[0].curProtPhsOvrCurr.phc51_table[i].Elmnt = strData;

        parRc = ::eAppParameterGetTableStringValue("51_Table", "511DirCont", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511DirCont : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 511DirCont is empty");
        }
        confData[0].curProtPhsOvrCurr.phc51_table[i].DirCont = strData;

        parRc = ::eAppParameterGetTableFloat32Value("51_Table", "511Set", tableIndex, &confData[0].curProtPhsOvrCurr.phc51_table[i].Set);
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511Set : %d", parRc);
        }

        parRc = ::eAppParameterGetTableStringValue("51_Table", "511Char", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511Char : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 511Char is empty");
        }
        confData[0].curProtPhsOvrCurr.phc51_table[i].Char = strData;

        parRc = ::eAppParameterGetTableFloat32Value("51_Table", "511TimeMult", tableIndex, &confData[0].curProtPhsOvrCurr.phc51_table[i].TimeMult);
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511TimeMult : %d", parRc);
        }

        parRc = ::eAppParameterGetTableFloat32Value("51_Table", "511Delay", tableIndex, &confData[0].curProtPhsOvrCurr.phc51_table[i].Delay);
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511Delay : %d", parRc);
        }

        parRc = ::eAppParameterGetTableFloat32Value("51_Table", "511MinOPTime", tableIndex, &confData[0].curProtPhsOvrCurr.phc51_table[i].MinOPTime);
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511MinOPTime : %d", parRc);
        }

        parRc = ::eAppParameterGetTableFloat32Value("51_Table", "511FollowerDTL", tableIndex, &confData[0].curProtPhsOvrCurr.phc51_table[i].FollowerDTL);
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511FollowerDTL : %d", parRc);
        }

        parRc = ::eAppParameterGetTableStringValue("51_Table", "511Rst", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511Rst : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 511Rst is empty");
        }
        confData[0].curProtPhsOvrCurr.phc51_table[i].Rst = strData;

        parRc = ::eAppParameterGetTableStringValue("51_Table", "511VtsActn", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511VtsActn : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 511VtsActn is empty");
        }
        confData[0].curProtPhsOvrCurr.phc51_table[i].VtsActn = strData;

        parRc = ::eAppParameterGetTableStringValue("51_Table", "511InrshActn", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 511InrshActn : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 511InrshActn is empty");
        }
        confData[0].curProtPhsOvrCurr.phc51_table[i].InrshActn = strData;

        i++;
        tableIndex++;
        parRc = ::eAppParameterDiscoverNextTableIndex("51_Table", tableIndex, &tableIndex);

    }

    //Table - PhaseOC_table
    tableIndex = 0;
    i = 0;
    parRc = ::eAppParameterDiscoverRecordNumInst(eAppPar_DbInst_App, "PhaseOC_table", &noOfRows);
    if (parRc != eAppPar_GetResult_OK)
    {
        EAPP_LOG_FAT("get table 'PhaseOC_table', reading table rows failed : %d ", parRc);
    }
    parRc = ::eAppParameterDiscoverNextTableIndex("PhaseOC_table", tableIndex, &tableIndex);
    while (parRc == eAppPar_GetResult_OK)
    {
        parRc = ::eAppParameterGetTableStringValue("PhaseOC_table", "GroupName", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column GroupName : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param GroupName is empty");
        }
        confData[0].curProtPhsOvrCurr.PhaseOC_table[i].GroupName = strData;

        parRc = ::eAppParameterGetTableStringValue("PhaseOC_table", "501Elmnt", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 501Elmnt : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 501Elmnt is empty");
        }
        confData[0].curProtPhsOvrCurr.PhaseOC_table[i].Elmnt = strData;

        parRc = ::eAppParameterGetTableStringValue("PhaseOC_table", "501DirCont", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 501DirCont : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 501DirCont is empty");
        }
        confData[0].curProtPhsOvrCurr.PhaseOC_table[i].DirCont = strData;

        parRc = ::eAppParameterGetTableFloat32Value("PhaseOC_table", "501Set", tableIndex, &confData[0].curProtPhsOvrCurr.PhaseOC_table[i].Set);
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 501Set : %d", parRc);
        }

        parRc = ::eAppParameterGetTableFloat32Value("PhaseOC_table", "501Delay", tableIndex, &confData[0].curProtPhsOvrCurr.PhaseOC_table[i].Delay);
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 501Delay : %d", parRc);
        }

        parRc = ::eAppParameterGetTableStringValue("PhaseOC_table", "501VtsActn", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 501VtsActn : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 501VtsActn is empty");
        }
        confData[0].curProtPhsOvrCurr.PhaseOC_table[i].VtsActn = strData;

        parRc = ::eAppParameterGetTableStringValue("PhaseOC_table", "501InrshActn", tableIndex, strData, sizeof(strData));
        if (parRc != eAppPar_GetResult_OK)
        {
            EAPP_LOG_FAT("Falied to read table column 501InrshActn : %d", parRc);
        }
        if (strData[0] == emptyChar)
        {
            EAPP_LOG_FAT("Param 501InrshActn is empty");
        }
        confData[0].curProtPhsOvrCurr.PhaseOC_table[i].InrshActn = strData;

        i++;
        tableIndex++;
        parRc = ::eAppParameterDiscoverNextTableIndex("PhaseOC_table", tableIndex, &tableIndex);

    }

    strData[0] = emptyChar;
}




