import React from 'react';
import { Outlet } from 'react-router-dom';

import { DisplayExtendedMenuStore } from '../../store';
import NavigationBar from '../NavigationBar/NavigationBar';
import Menu from '../Menu/Menu';


import styles from './App.module.css';




function App() {
    const displayExtendedMenu = DisplayExtendedMenuStore((state) => state.value);
	


	return (
    	<div className={styles.appMain + " " + (displayExtendedMenu.data ? styles.displayExtendedMenu : styles.normal)}>
			<div className={styles.navigationBar}>
				<NavigationBar/>
			</div>
			<div className={styles.menu}>
				<Menu/>
			</div>
			<div className={styles.mainContent}>
				<Outlet/>
			</div>
    	</div>
  	);
}

export default App;
