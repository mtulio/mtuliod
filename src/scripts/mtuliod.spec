Name: mtuliod

Version: 0.1-beta
Release: 1

License: GPL
URL: http://github.com/mtulio/mtuliod

Group: System Environment/Base
Summary: Utilities for configuration system remotly

Buildroot: %{name}-%{version}
Source: %{name}-%{version}.tar.gz

%description
This package contains utilities for configuring the linux resources, 
such as get remote hostname and change user password (might to be improve
the security)

%prep
%setup -q

%build
make

%install
rm -rf %{buildroot}

mkdir -p %{buildroot}%{_sbindir}
mkdir -p %{buildroot}%{_includedir}
mkdir -p %{buildroot}%{_libdir}
install -m755 src/mtuliod %{buildroot}%{_sbindir}

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

%files
%defattr (-,root,root)
%doc AUTHORS COPYING
%{_sbindir}/mtuliod

%changelog
* Wed Oct 18 2015 Marco Tulio R Braga <admin@mtulio.eng.br>
- initial cleanup of spec file from net release
