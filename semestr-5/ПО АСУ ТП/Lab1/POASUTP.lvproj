﻿<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="11008008">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="VirLab1" Type="Folder">
			<Item Name="Zadanie1.vi" Type="VI" URL="../Zadanie1.vi"/>
			<Item Name="Zadanie2.vi" Type="VI" URL="../Zadanie2.vi"/>
			<Item Name="Zadanie3.vi" Type="VI" URL="../Zadanie3.vi"/>
		</Item>
		<Item Name="VirLab2" Type="Folder">
			<Item Name="Zadanie4.vi" Type="VI" URL="../../Laba2/Zadanie4.vi"/>
		</Item>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
