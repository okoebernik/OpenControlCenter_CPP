idf_component_register(
    SRCS
        "main.cpp"

        "app/Application.cpp"
		
		"core/EventBus.cpp"
        "core/LayoutManager.cpp"
		"core/ScreenManager.cpp"
		"core/ServiceManager.cpp"
		"core/Configuration.cpp"
		
		"ui/DashboardScreen.cpp"
        "ui/SplashScreen.cpp"
        "ui/Theme.cpp"
        "ui/StatusBar.cpp"
        
        "ui/NavigationBar.cpp"
		"ui/SettingsScreen.cpp"
        
		"widgets/Card.cpp"
		"widgets/MetricRow.cpp"
		"widgets/PrimaryValue.cpp"
		"widgets/SystemCard.cpp"
		"widgets/IconButton.cpp"
		"widgets/ValueEditor.cpp"
		
		"models/SystemModel.cpp"
		"models/ClockModel.cpp"
		"models/WiFiModel.cpp"
		"models/SettingsModel.cpp"
		
		"viewmodels/DashboardViewModel.cpp"
		"viewmodels/StatusBarViewModel.cpp"
		"viewmodels/SettingsViewModel.cpp"
		
		"services/SystemService.cpp"
		"services/ClockService.cpp"
		"services/WiFiService.cpp"
		
		"hardware/WiFiHardware.cpp"
		"hardware/PreferencesHardware.cpp"
		
    INCLUDE_DIRS
        "."
        "app"
        "core"
        "ui"
        "widgets"
        "services"
        "models"
		"viewmodels"
		"secrets"
		"hardware"
)

target_compile_features(${COMPONENT_LIB} PRIVATE cxx_std_17)