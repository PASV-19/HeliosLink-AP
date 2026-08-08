"""
URL configuration for helioslink project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/6.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""

from django.contrib import admin
from django.urls import path
from webapp import views
from webapp import api_views
#Password recovery import
from django.contrib.auth import views as auth_views

urlpatterns = [
    path("admin/", admin.site.urls),

    #Login/Users related
    path('', views.login_view, name='login'),
    path('crear-cuenta/', views.crear_cuenta, name='crear_cuenta'),
    path('logout/', views.logout_view, name="logout"),

    #Password recovery
    path('restablecer/', auth_views.PasswordResetView.as_view(template_name='restablecer.html',), name='restablecer'),
    path('password-reset/', auth_views.PasswordResetDoneView.as_view(template_name='password_reset_done.html'), name='password_reset_done',),
    path('reset/<uidb64>/<token>/', auth_views.PasswordResetConfirmView.as_view(template_name='password_reset_confirm.html'), name='password_reset_confirm',),
    path('reset/done/', auth_views.PasswordResetCompleteView.as_view(template_name='password_reset_complete.html'), name='password_reset_complete',),
    
    #Real time page / ESP32 redirection
    path('dashboard', views.dashboard, name='dashboard'),

    #Informative pages / non real-time data
    path('graf-info/', views.graf_info_view, name='graf_info'),
    # Merged with graf-info #path('graf-hist/', views.graf_hist_view, name='graf_hist'),
    path('reportes/', views.reportes_view, name='reportes'),
    path("reportes/pdf/", views.generar_pdf, name="generar_pdf"),
    path('user-info/', views.user_info_view, name='user_info'),
    path('net-info/', views.net_info_view, name='net_info'),

    # API Endpoints
    path("api/telemetry/", api_views.api_telemetry_post),
    path("api/battery/", api_views.api_battery_get),
]
