import { useEffect, useState } from "react";
import { useQuery, useMutation } from "@tanstack/react-query";

import { UserData, PageOptions } from "../../types";
import { SelectedPageStore } from "../../store";

import { UserCredentials, authenticate } from "../../api/UserDataAPI"

import { fetchOptionsGET, fetchOptionsPOST} from '../fetchOptions';

import styles from "./AuthenticationPageStyles.module.css";
import { useUserData } from "../../customHooks/useUserData";


function AuthenticationPage() {
    const selectedPage = SelectedPageStore((state) => state.value);
    const [displaySignUpPage, setDisplaySignUpPage] = useState(false);
    const [enteredUsername, setEnteredUsername] = useState(true);
    const [enteredPassword, setEnteredPassword] = useState(true);
    const [passwordsMatch, setPasswordsMatch] = useState(true);

    const [username, setUsername] = useState<string>("");
    const [password, setPassword] = useState("");
    const [confirmPassword, setConfirmPassword] = useState("");

    const [displayLoading, setDisplayLoading] = useState(false);
    const [displayUserDoesNotExist, setDisplayUserDoesNotExist] = useState(false);
    const [displayIncorrectPassoword, setDisplayIncorrectPassoword] = useState(false);

    const userData = useUserData();
    
    
    
    useEffect(() => {
        selectedPage.setSelectedPage(PageOptions.SignInSignUp);
    }, []);

    useEffect(() => {
        if (!userData.loadingUserData) {
            switch (userData.data.userStatus) {
                case -1: {
                    setDisplayUserDoesNotExist(true);
                    break;
                }
                case 0: {
                    setDisplayIncorrectPassoword(true);
                    break;
                }
                case 1: {
                    console.log("other stuff happens");
                    break;
                }
                default: {
                    break;
                }
            }

        }
    }, [userData.data, userData.loadingUserData]);

    function authenticateUser() {
        const userCredentials: UserCredentials = {
            username: username,
            password: password,
            createUser: displaySignUpPage,
        }
        userData.authenticateUser(userCredentials);
    }

    function userNameOnInput(event: any) {
        setUsername(event.target.value);
        if (!enteredUsername) {
            setEnteredUsername(true);
        }
        if (displayUserDoesNotExist) {
            setDisplayUserDoesNotExist(false);
        }
    }

    function passwordOnInput(event: any) {
        setPassword(event.target.value);
        if (!enteredPassword) {
            setEnteredPassword(true);
        }
        if (!passwordsMatch) {
            setPasswordsMatch(true);
        }
        if (displayIncorrectPassoword) {
            setDisplayIncorrectPassoword(false);
        }
    }

    function passwordConfirmOnInput(event: any) {
        setConfirmPassword(event.target.value);
        if (!passwordsMatch) {
            setPasswordsMatch(true);
        }
    }

    function signInSignUpOnClick() {
        if (username === "") {
            setEnteredUsername(false);
        }
        else if (password === "") {
            setEnteredPassword(false);
        }
        else if (displaySignUpPage && password !== confirmPassword) {
            setPasswordsMatch(false);
        }
        else {
            authenticateUser();
            setDisplayLoading(true);
            setUsername("");
            setPassword("");
            setConfirmPassword("");
        }
    }
    
    function SignInSignUpButtonText() {
        if (displayLoading) {
            return "Loading...";
        }
        else if (!enteredUsername) {
            return "Enter Username";
        }
        else if (!enteredPassword) {
            return "Enter Password";
        }
        else {
            return ("Sign " + (displaySignUpPage ? "Up" : "In"));
        }
    }

    function SwitchPageButtonOnClick() {
        setDisplaySignUpPage(!displaySignUpPage);
        setEnteredUsername(true);
        setEnteredPassword(true);
        setPasswordsMatch(true);
        setConfirmPassword("");
    }

    return (
        <div className={styles.page}>
            <div id={(displaySignUpPage && !passwordsMatch ? styles.signUpExtend : "")} className={styles.main + " " + (displaySignUpPage ? styles.signUp : styles.signIn)}>
                <h1>Sign {displaySignUpPage ? "Up" : "In"}</h1>

                <input type="text" className={styles.inputUserName} value={username} placeholder="Username" onInput={(event: any) => userNameOnInput(event)} />
                <input id={(displaySignUpPage && !passwordsMatch ? styles.passwordNotMatchInput : "")} type="password" className={styles.inputUserPassword} value={password} placeholder="Password" onInput={(event: any) => passwordOnInput(event)} />
                {displaySignUpPage ? <input id={(!passwordsMatch ? styles.passwordNotMatchInput : "")} type="password" className={styles.inputUserPasswordConfirm} value={confirmPassword} placeholder="Confirm Password" onInput={(event: any) => passwordConfirmOnInput(event)}/> : ""}
                {(displaySignUpPage && !passwordsMatch) ? <p className={styles.importantInfo}>Passwords do not match</p> : ""}
                {(!displaySignUpPage && displayUserDoesNotExist) ? <p className={styles.importantInfo}>User does not exist</p> : ""}
                {(!displaySignUpPage && displayIncorrectPassoword) ? <p className={styles.importantInfo}>Password Mismatch</p> : ""}
                <button className={styles.signInUpButton} onClick={() => signInSignUpOnClick()}>{SignInSignUpButtonText()}</button>
                <button className={styles.switchPageButton} onClick={() => SwitchPageButtonOnClick()}>Switch to Sign {displaySignUpPage ? "In" : "Up"}</button>
            </div>
        </div>
    );
}

export default AuthenticationPage;