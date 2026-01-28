import React from 'react';
import { Outlet } from 'react-router-dom';

import { DisplayExtendedMenuStore } from '../../store';
import NavigationBar from '../NavigationBar/NavigationBar';
import Menu from '../Menu/Menu';


import styles from './App.module.css';

import { fetchOptionsGet } from '../fetchOptions';

function test() {
	fetch("http://localhost:3490", fetchOptionsGet)
	.then((response) => {
		return response.text();
	})
	.then((data) => {
		console.log("Data Recieved: " + data);
	})
	.catch((error) => {
		console.error(error);
	});
}

function App() {
    const displayExtendedMenu = DisplayExtendedMenuStore((state) => state.value);

	test();

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
