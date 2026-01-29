import React from 'react';
import { Outlet } from 'react-router-dom';

import { DisplayExtendedMenuStore } from '../../store';
import NavigationBar from '../NavigationBar/NavigationBar';
import Menu from '../Menu/Menu';


import styles from './App.module.css';

import { fetchOptionsGet, fetchOptionsPOST} from '../fetchOptions';

function test() {
	const ex = {
		"name" : "a name",
		"stuff": 56,
	}
	fetch("http://localhost:3490", {...fetchOptionsPOST,
		headers: {
			"Content-Type": "applcation/json",
		},
		body: JSON.stringify(ex),
	})
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
