idf_component_register(
    SRCS
        "main.cpp"

        "app/Application.cpp"
		
		"core/EventBus.cpp"
        "core/LayoutManager.cpp"
		"core/ScreenManager.cpp"
		"core/ServiceManager.cpp"
		
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
		
		"models/SystemModel.cpp"
		"models/ClockModel.cpp"
		
		"viewmodels/DashboardViewModel.cpp"
		
		"services/SystemService.cpp"
		"services/ClockService.cpp"
		
    INCLUDE_DIRS
        "."
        "app"
        "core"
        "ui"
        "widgets"
        "services"
        "models"
		"viewmodels"
)

target_compile_features(${COMPONENT_LIB} PRIVATE cxx_std_17)