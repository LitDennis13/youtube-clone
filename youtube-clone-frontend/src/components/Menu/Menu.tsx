import { useState, useEffect } from "react";

import { DisplayExtendedMenuStore } from "../../store";


import styles from "./MenuStyles.module.css";

import homeIcon from "../../images/home.svg";
import subscriptionsIcon from "../../images/subscriptions.svg";
import historyIcon from "../../images/history.svg";
import playlistsIcon from "../../images/playlists.svg";
import videosIcon from "../../images/videos.svg";

function Menu() {
    const displayExtendedMenu = DisplayExtendedMenuStore((state) => state.value);

    useEffect(() => {
        if (displayExtendedMenu.data) {
            console.log("display extended menu");
        } else {
            console.log("do not display extended menu");
        }
    }, [displayExtendedMenu.data]);

    return (
        displayExtendedMenu.data ? 
        <div className={styles.menuExtended}>
            
        </div>
        :
        <div className={styles.menuNormal}>
            <button className={styles.homeButton}>
                <img src={homeIcon} alt="home icon" />Home
            </button>
            <button className={styles.subscriptionsButton}>
                <img src={subscriptionsIcon} alt="subscriptions icon" />Subscriptions
            </button>
            <button className={styles.historyButton}>
                <img src={historyIcon} alt="history icon" />History
            </button>
            <button className={styles.playListsButton}>
                <img src={playlistsIcon} alt="playlists icon" />Playlists
            </button>
            <button className={styles.myVideosButton}>
                <img src={videosIcon} alt="my videos icon" />My Videos
            </button>
        </div>
    );

}

export default Menu;