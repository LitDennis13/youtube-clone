import React from 'react';
import styles from './App.module.css';

import NavigationBar from './components/NavigationBar/NavigationBar';

function App() {
	return (
    	<div className={styles.appMain}>
			<div className={styles.navigationBar}>
				<NavigationBar/>
			</div>
    	</div>
  	);
}

export default App;
