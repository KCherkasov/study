"""ask_cherkasov URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.10/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin
from django.conf.urls.static import static
from ask_cherkasov import views, settings

urlpatterns = [
  url(r'^admin/', admin.site.urls, name="admin"),
  url(r'^base/', views.base, name="base"),
  url(r'^base-no-auth/', views.base_noauth, name="base-noauth"),
  url(r'^index/', views.index, name="index"),
  url(r'^index-no-auth/', views.index_noauth, name="index-noauth"),
  url(r'^question/', views.question, name="question"),
  url(r'^question-no-auth/', views.question_noauth, name="question-noauth"),
  url(r'^question-author/', views.question_author, name="question-author"),
  url(r'^ask/', views.ask, name="ask"),
  url(r'^ask-errs/', views.ask_werrs, name="ask-werrs"),
  url(r'^login/', views.login, name="sign-in"),
  url(r'^login-errs/', views.login_werrs, name="sign-in-werrs"),
  url(r'^signup/', views.signup, name="sign-up"),
  url(r'^signup-errs/', views.signup_werrs, name="sign-up-werrs"),
  url(r'^edit/', views.edit, name="profile-edit"),
  url(r'^edit-errs/', views.edit_werrs, name="profile-edit-werrs"), 
] + static(settings.MEDIA_URL, document_root = settings.MEDIA_ROOT)
