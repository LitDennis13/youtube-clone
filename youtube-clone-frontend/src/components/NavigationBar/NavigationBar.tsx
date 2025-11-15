import { useState } from "react";
import { Link } from "react-router-dom";

import { UserLoggedInStore, DisplayExtendedMenuStore } from "../../store";

import styles from "./NavigationBarStyles.module.css";

import fakeYoutubeLogo from "../../images/fake youtube logo.svg";
import fakeYoutubeCloneLetters from "../../images/youtube clone.svg";
import menuIcon from "../../images/menu.svg";
import searchIcon from "../../images/search icon.svg";
import accountCircle from "../../images/account circle.svg";
import uploadIcon from "../../images/upload.svg";

function NavigationBar() {
    const userLoggedIn = UserLoggedInStore((state) => state.value);

    const displayExtendedMenu = DisplayExtendedMenuStore((state) => state.value);

    const [searching, setSearching] = useState(false);

    function menuButtonOnClick() {
        displayExtendedMenu.setDisplayExtendedMenu(!displayExtendedMenu.data);
    }

    return (
        <div className={styles.navigationBarMain}>
            <div className={styles.leftSection}>
                <button className={styles.menuButton} onClick={() => menuButtonOnClick()}>
                    <img src={menuIcon} alt="menu button" />
                </button>

                <Link to={"/"} className={styles.homeLink}>
                    <button className={styles.logoButton}>
                        <img src={fakeYoutubeLogo} alt="fake youtube logo" />
                        <img src={fakeYoutubeCloneLetters} alt="fake youtube letters" />
                    </button>
                </Link>
            </div>
            
            <div className={styles.middleSection}>
                <input className={styles.searchBar} placeholder="Search" type="text" onFocus={() => setSearching(true)} onBlur={() => setSearching(false)} />
                <button className={styles.searchButton}>
                    <img src={searchIcon} alt="search icon" />
                </button>
            </div>

            <div className={styles.rightSection + " " + (userLoggedIn.data ? styles.loggedIn : styles.notLoggedIn)}>
                {userLoggedIn.data ? 
                <div className={styles.loggedInBar}>
                    <Link to={"/upload-video"} className={styles.uploadVideoButtonLink}>
                        <button className={styles.uploadVideoButton}>
                                <img src={uploadIcon} alt="upload video icon" />Upload Video
                        </button>
                    </Link>

                    <button className={styles.profileIcon}>
                        <img src={accountCircle} alt="Account circle" />
                    </button>
                </div>
                :
                <button className={styles.signInButton}>
                    <img src={accountCircle} alt="Account circle" />
                    Sign In
                </button>
                }
            </div>

        </div>
    );
}


export default NavigationBar;
