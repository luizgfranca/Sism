%global __brp_check_rpaths %{nil}

Name:           sism
Version:        <<version>>
Release:        1%{?dist}
Summary:        Services manager for GNU/Linux operating systems

License:        AGPLv3
URL:            https://github.com/luizgfranca/Sism
Source0:        %{name}-%{version}.tar.gz

Requires:       libsigc++
Requires:       pkgconf-pkg-config
Requires:       glib2
Requires:       pango
Requires:       cairo
Requires:       gdk-pixbuf2
Requires:       graphene
Requires:       gtk4
Requires:       glibmm2.68
Requires:       cairomm
Requires:       pangomm
Requires:       gtkmm4.0
Requires:       sdbus-cpp

%description
Services manager for GNU/Linux operating systems.

%prep
%setup -q

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{_bindir}
mkdir -p $RPM_BUILD_ROOT/%{_datadir}/applications
mkdir -p $RPM_BUILD_ROOT/%{_datadir}/icons
cp %{name} $RPM_BUILD_ROOT/%{_bindir}
cp %{name}.desktop $RPM_BUILD_ROOT/%{_datadir}/applications
cp %{name}.svg $RPM_BUILD_ROOT/%{_datadir}/icons

%clean
rm -rf $RPM_BUILD_ROOT

%files
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/%{name}.svg

%changelog
* Thu Nov 09 2023 luizgfranca <luizgfc@proton.me>
