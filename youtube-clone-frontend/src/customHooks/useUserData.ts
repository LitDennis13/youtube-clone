import { useEffect } from "react";
import { useMutation, useQuery, useQueryClient } from "@tanstack/react-query";

import { fetchUserData, authenticate } from "../api/UserDataAPI";
import { UserData } from "../types";

export function useUserData() {
    const queryClient = useQueryClient();

    const { data: userData, isLoading: loadingUserData } = useQuery({
        queryKey: ["userData"],
        queryFn: () => fetchUserData(),
    });

    const { mutateAsync: authenticateUser, isSuccess: setAuthenticateUserSuccess } = useMutation({
        mutationFn: authenticate,
    });

    useEffect(() => {
        const condition = setAuthenticateUserSuccess;
        if (condition) {
            queryClient.invalidateQueries({queryKey: ["userData"]});
        }

    }, [setAuthenticateUserSuccess]);

    return {
        data: (userData as UserData),
        authenticateUser,
        loadingUserData,
    };
    
}